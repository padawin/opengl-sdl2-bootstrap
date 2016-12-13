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

#include "RenderableCollection.hpp"
#include "EntityCollection.hpp"

#include "Player.hpp"
#include "Asteroid.hpp"

#define GLSL(src) "#version 150 core\n" #src

SDL_Window* window;
SDL_GLContext context;
RenderableCollection g_renderables;
EntityCollection g_entityCollection;
GLuint vertexShader;
GLuint fragmentShader;
GLuint shaderProgram;

const int NB_ASTEROIDS = 10;
Player g_player;
Asteroid g_asteroids[NB_ASTEROIDS];

int initSDL(const char* title, const int x, const int y, const int w, const int h);
void initGL();
void createShaders();
void createTextures();
void createShapes();
void mainLoop(GLuint shaderProgram);
bool handleEvents();
void update(GLuint shaderProgram);
void setCamera(GLuint shaderProgram);
void setFieldOfView(GLuint shaderProgram);
void render();
void cleanSDL();

void generateEntities() {
	g_player.setPosition(Vector3D(0.0f, 0.0f, 0.0f));
	g_entityCollection.addEntity(&g_player);

	time_t t;
	srand((unsigned) time(&t));
	for (int a = 0; a < NB_ASTEROIDS; ++a) {
		g_asteroids[a].setCenter(Vector3D(0.5f, 0.5f, 0.5f));
		g_asteroids[a].setPosition(Vector3D(
			((rand() % 4000) - 2000) / 1000.0f,
			((rand() % 4000) - 2000) / 1000.0f,
			0
		));
		g_asteroids[a].setAngularSpeed(Vector3D(1.0f, 1.0f, 0.0f));
		g_entityCollection.addEntity(&g_asteroids[a]);
	}
}

int main(int argc, char *argv[])
{
	initSDL("OpenGL", 0, 0, 800, 600);
	initGL();
	createShaders();
	createShapes();
	createTextures();
	generateEntities();
	mainLoop(shaderProgram);

	glDeleteProgram(shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);
	g_renderables.clean();
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
		}
	}

	return l_bReturn;
}

void initGL() {
	glewExperimental = GL_TRUE;
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE); // cull face
	glCullFace(GL_BACK); // cull back face
	glFrontFace(GL_CCW); // GL_CCW for counter clock-wise
}

void createShaders() {
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

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
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
				// this inverts the bottom half of the texture
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

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	// link the shaders in a program to be used
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);
}

void createTextures() {
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
}

void createShapes() {
	g_renderables.addShape(SHIP);
	g_renderables.addShape(ASTEROID);
	g_renderables.generateBuffers();
	g_renderables.generateVertexArrays(shaderProgram);
}

void mainLoop(GLuint shaderProgram) {
	bool running = true;
	while (running) {
		running = handleEvents();

		update(shaderProgram);

		setCamera(shaderProgram);
		setFieldOfView(shaderProgram);

		render();
	}
}

bool handleEvents() {
	SDL_Event event;
	bool running = true;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				running = false;
				break;

			case SDL_KEYDOWN:
				break;
		}
	}

	return running;
}

void update(GLuint shaderProgram) {
	g_entityCollection.update();
}

// Needs to provide player's information
void setCamera(GLuint shaderProgram) {
	glm::mat4 view = glm::lookAt(
		// camera's position
		glm::vec3(1.0f, 0.0f, 5.0f),
		// point where the camera is aiming at (eg player's position)
		glm::vec3(0.0f, 0.0f, 0.0f),
		// "up" vector of the camera, for its orientation, based on player's
		// orientation
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
	GLint uniView = glGetUniformLocation(shaderProgram, "view");
	glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
}

// based on player's speed?
void setFieldOfView(GLuint shaderProgram) {
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 10.0f);
	GLint uniProj = glGetUniformLocation(shaderProgram, "proj");
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));
}

void render() {
	// Clear the screen to black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUniform1i(glGetUniformLocation(shaderProgram, "time"), SDL_GetTicks());
	g_entityCollection.render(shaderProgram, g_renderables);

	SDL_GL_SwapWindow(window);
}

void cleanSDL() {
	SDL_GL_DeleteContext(context);
	SDL_Quit();
}
