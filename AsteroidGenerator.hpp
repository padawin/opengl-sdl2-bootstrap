#ifndef __ASTEROID_GENERATOR__
#define __ASTEROID_GENERATOR__

#include <vector>
#include "Asteroid.hpp"

#define NB_MAX_ASTEROIDS 200

class AsteroidGenerator {
	private:
	std::vector<Asteroid*> m_vAsteroids;
	void _removeAsteroid(unsigned int asteroidIndex);

	public:
	void addAsteroid(Vector3D position);
	void update(Vector3D thresholdPosition, float threshold);
	std::vector<Asteroid*> getAsteroids();
	void clean();
};

#endif
