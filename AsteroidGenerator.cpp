#include "AsteroidGenerator.hpp"

Asteroid* AsteroidGenerator::addAsteroid(Vector3D position) {
	if (m_iNbAsteroids == NB_MAX_ASTEROIDS) {
		return NULL;
	}

	Asteroid *asteroid = new Asteroid();
	asteroid->setPosition(position);
	asteroid->setAngularSpeed(
		Vector3D(1.0f, 1.0f, 0.0f)
	);
	m_asteroids[m_iNbAsteroids] = asteroid;
	++m_iNbAsteroids;

	return asteroid;
}

void AsteroidGenerator::clean() {
	for (unsigned int a = 0; a < m_iNbAsteroids; ++a) {
		free(m_asteroids[a]);
	}
}
