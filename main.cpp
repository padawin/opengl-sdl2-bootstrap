// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

SDL_Window* window;
SDL_GLContext context;

int initSDL(const char* title, const int x, const int y, const int w, const int h);
void cleanSDL();

int main(int argc, char *argv[])
{
	initSDL("OpenGL", 0, 0, 100, 100);

	SDL_Event windowEvent;
	while (true) {
		if (SDL_PollEvent(&windowEvent)) {
			if (windowEvent.type == SDL_QUIT) {
				break;
			}
		}

		SDL_GL_SwapWindow(window);
	}

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

void cleanSDL() {
	SDL_GL_DeleteContext(context);
	SDL_Quit();
}
