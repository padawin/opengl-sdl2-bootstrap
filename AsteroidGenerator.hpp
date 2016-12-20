#ifndef __ASTEROID_GENERATOR__
#define __ASTEROID_GENERATOR__

#include <vector>
#include "Asteroid.hpp"

#define NB_MAX_ASTEROIDS 20

class AsteroidGenerator {
	private:
	std::vector<Asteroid*> m_vAsteroids;
	float m_fDistanceRecycle;
	unsigned int m_iMinDistanceAppear;
	unsigned int m_iMaxDistanceAppear;
	void _removeAsteroid(unsigned int asteroidIndex);
	void _generateAsteroids(Vector3D thresholdPosition);

	public:
	void setDistanceRecycle(float distance);
	void setRangeDistanceAppear(unsigned int minDistance, unsigned int maxDistance);
	void addAsteroid(Vector3D position);
	void update(Vector3D thresholdPosition);
	std::vector<Asteroid*> getAsteroids();
	void clean();
};

#endif
