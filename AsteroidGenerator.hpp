#ifndef __ASTEROID_GENERATOR__
#define __ASTEROID_GENERATOR__

#include "Asteroid.hpp"

#define NB_MAX_ASTEROIDS 200

class AsteroidGenerator {
	private:
	Asteroid *m_asteroids[NB_MAX_ASTEROIDS];
	unsigned int m_iNbAsteroids;

	public:
	AsteroidGenerator() : m_iNbAsteroids(0) {}
	Asteroid* addAsteroid(Vector3D position);
	void clean();
};

#endif
