#ifndef __ENGINE__
#define __ENGINE__

#include <SDL2/SDL.h>

#include "RenderableCollection.hpp"
#include "EntityCollection.hpp"
#include "Player.hpp"
#include "AsteroidGenerator.hpp"

#define GLSL(src) "#version 150 core\n" #src
#define MIN_DISTANCE_ASTEROID_GENERATE 10
#define MAX_DISTANCE_ASTEROID_GENERATE 13
#define MAX_DISTANCE_FROM_PLAYER 13

const int NB_MAX_INIT_ASTEROIDS = 20;

class Engine {
	private:
	SDL_Window* m_window;
	SDL_GLContext m_context;
	RenderableCollection m_renderables;
	GLuint m_vertexShader;
	GLuint m_fragmentShader;
	GLuint m_shaderProgram;

	Player m_player;
	AsteroidGenerator m_asteroidGenerator;
	EntityCollection m_entityCollection;

	int _initSDL(const char* title, const int x, const int y, const int w, const int h);
	void _initGL();
	void _generateEntities();
	void _createShaders();
	void _createTextures();
	void _createShapes();
	bool _handleEvents();
	void _update();
	void _setCamera();
	void _setFieldOfView();
	void _render();
	void _cleanSDL();

	public:
	void init(unsigned int screenWidth, unsigned int screenHeight);
	void run();
	void clean();
};

#endif
