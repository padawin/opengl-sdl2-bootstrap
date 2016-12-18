#include "AsteroidGenerator.hpp"

Asteroid* AsteroidGenerator::addAsteroid(Vector3D position) {
	if (m_iNbAsteroids == NB_MAX_ASTEROIDS) {
		return NULL;
	}

	Asteroid *asteroid = new Asteroid();
	asteroid->setPosition(position);
	// angle is between -2.0f and 2.0f degrees
	float angularSpeedX = rand() % 4 - 2.0f,
		  angularSpeedY = rand() % 4 - 2.0f,
		  angularSpeedZ = rand() % 4 - 2.0f;
	asteroid->setAngularSpeed(
		Vector3D(angularSpeedX, angularSpeedY, angularSpeedZ)
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
