// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#define GLSL(src) "#version 150 core\n" #src

SDL_Window* window;
SDL_GLContext context;

int initSDL(const char* title, const int x, const int y, const int w, const int h);
void cleanSDL();

int main(int argc, char *argv[])
{
	initSDL("OpenGL", 0, 0, 400, 400);

	float vertices[] = {
		0.5f,  0.5f, // Vertex 1 (X, Y)
		0.5f, -0.5f, // Vertex 2 (X, Y)
		-0.5f, -0.5f,  // Vertex 3 (X, Y)
		-0.5f, 0.5f // Vertex 2 (X, Y)
	};

	GLuint elements[] = {
		0, 1, 2,
		2, 3, 0
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
		in vec2 position;

		void main() {
			gl_Position = vec4(position, 0.0, 1.0);
		}
	);

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	// Create and compile the fragment shader
	const char* fragmentSource = GLSL(
		uniform vec3 triangleColor;
		out vec4 outColor;

		void main() {
			outColor = vec4(triangleColor, 1.0f);
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
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// manipulate the triangle's color
	GLint uniColor = glGetUniformLocation(shaderProgram, "triangleColor");
	glUniform3f(uniColor, 1.0f, 0.0f, 0.0f);

	SDL_Event event;
	bool running = true;
	while (running) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					running = false;
					break;

				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_UP) {
						glUniform3f(uniColor, 0.0f, 1.0f, 0.0f);
					}
					else if (event.key.keysym.sym == SDLK_DOWN) {
						glUniform3f(uniColor, 0.0f, 0.0f, 1.0f);
					}
					break;
			}
		}

		// Clear the screen to black
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw a triangle from the 3 vertices
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
