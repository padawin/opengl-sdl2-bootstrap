#ifndef __ASTEROID_GENERATOR__
#define __ASTEROID_GENERATOR__

#include <vector>
#include "Asteroid.hpp"

#define NB_MAX_ASTEROIDS 20

class AsteroidGenerator {
	private:
	std::vector<Asteroid*> m_vAsteroids;
	float m_fDistanceRecycle;
	void _removeAsteroid(unsigned int asteroidIndex);

	public:
	void setDistanceRecycle(float distance);
	void addAsteroid(Vector3D position);
	void update(Vector3D thresholdPosition);
	std::vector<Asteroid*> getAsteroids();
	void clean();
};

#endif
