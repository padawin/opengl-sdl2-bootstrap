#include "Engine.hpp"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(int argc, char *argv[])
{
	time_t t;
	srand((unsigned) time(&t));
	Engine engine;

	engine.init(SCREEN_WIDTH, SCREEN_HEIGHT);
	engine.run();
	engine.clean();

	return 0;
}
