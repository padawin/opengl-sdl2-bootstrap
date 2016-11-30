// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include <SOIL.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

// for math transformations
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLSL(src) "#version 150 core\n" #src

SDL_Window* window;
SDL_GLContext context;

int initSDL(const char* title, const int x, const int y, const int w, const int h);
void cleanSDL();

int main(int argc, char *argv[])
{
	initSDL("OpenGL", 0, 0, 400, 400);

	float vertices[] = {
		// Position    Color             Texcoords
		// roof
		0.0f,   0.0f, 0.75f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.75f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.75f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		// walls
		0.5f,   0.0f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.5f, -0.75f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		0.5f,  -0.75f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.0f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f
	};

	GLuint elements[] = {
		0, 1, 2,
		3, 4, 5,
		4, 3, 6
	};

	// create vertex array object
	GLuint vertexArray;
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	// create vertex buffer object
	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	// copy the vertices in the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint elementsBuffer;
	glGenBuffers(1, &elementsBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementsBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	// Create and compile the vertex shader
	const char* vertexSource = GLSL(
		in vec3 position;
		in vec3 color;
		in vec2 texture;

		out vec3 Color;
		out vec2 Texture;

		uniform mat4 trans;
		uniform mat4 view;
		uniform mat4 proj;

		void main()
		{
			Color = color;
			Texture = texture;
			gl_Position = proj * view * trans * vec4(position, 1.0);
		}
	);

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	// Create and compile the fragment shader
	const char* fragmentSource = GLSL(
		in vec3 Color;
		in vec2 Texture;

		out vec4 outColor;
		uniform sampler2D avatar;
		uniform int time;

		void main()
		{
			if (Texture.x == 0.0f && Texture.y == 0.0f) {
				outColor = vec4(Color, 1.0);
			}
			else if (Texture.y < 0.5f) {
				outColor = texture(avatar, Texture);
			}
			else {
				//outColor = texture(tex, vec2(Texture.x, 1.0f - Texture.y));
				outColor = texture(
					avatar,
					vec2(
						Texture.x + sin(Texture.y * 60.0 + time / 100.0) / 30.0,
						1.0 - Texture.y
					)
				) * vec4(0.7, 0.7, 1.0, 1.0);
			}
		}
	);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	// link the shaders in a program to be used
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	// Specify the layout of the vertex data
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);

	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(
		colAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))
	);

	GLint texAttrib = glGetAttribLocation(shaderProgram, "texture");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(
		texAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))
	);

	// textures
	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	int width, height;
	unsigned char* image;
	glActiveTexture(GL_TEXTURE0);
	image = SOIL_load_image("avatar.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glUniform1i(glGetUniformLocation(shaderProgram, "avatar"), 0);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glm::mat4 trans;

	SDL_Event event;
	bool running = true;
	while (running) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					running = false;
					break;

				case SDL_KEYDOWN:
					break;
			}
		}

		trans = glm::rotate(
			trans,
			glm::radians(3.0f),
			glm::vec3(1.0f, 1.0f, 0.0f)
		);
		GLint uniTrans = glGetUniformLocation(shaderProgram, "trans");
		glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
		glUniform1i(glGetUniformLocation(shaderProgram, "time"), SDL_GetTicks());

		// camera definition
		glm::mat4 view = glm::lookAt(
			glm::vec3(1.2f, 1.2f, 1.2f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 1.0f)
		);
		GLint uniView = glGetUniformLocation(shaderProgram, "view");
		glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
		// end of camera

		// Field of view
		glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 10.0f);
		GLint uniProj = glGetUniformLocation(shaderProgram, "proj");
		glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));
		// end field of view

		// Clear the screen to black
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw a triangle from the 3 vertices
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		SDL_GL_SwapWindow(window);
	}

	glDeleteProgram(shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteVertexArrays(1, &vertexArray);
	cleanSDL();
	return 0;
}

int initSDL(const char* title, const int x, const int y, const int w, const int h) {
	char l_bReturn = 1;
	int flags;
	flags = SDL_WINDOW_OPENGL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL Init failed\n");
		l_bReturn = 0;
	}
	else {
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
		window = SDL_CreateWindow(title, x, y, w, h, flags);
		if (window == 0) {
			printf("Window creation failed\n");
			l_bReturn = 0;
		}
		else {
			context = SDL_GL_CreateContext(window);
			glewExperimental = GL_TRUE;
			glewInit();
		}
	}

	return l_bReturn;
}

void cleanSDL() {
	SDL_GL_DeleteContext(context);
	SDL_Quit();
}
