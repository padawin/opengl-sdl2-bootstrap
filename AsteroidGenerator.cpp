#include "AsteroidGenerator.hpp"

void AsteroidGenerator::addAsteroid(Vector3D position) {
	if (m_vAsteroids.size() == NB_MAX_ASTEROIDS) {
		return;
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
	m_vAsteroids.push_back(asteroid);
}

void AsteroidGenerator::clean() {
	for (std::vector<Entity*>::size_type i = 0; i < m_vAsteroids.size(); ++i) {
		free(m_vAsteroids[i]);
	}
}

std::vector<Asteroid*> AsteroidGenerator::getAsteroids() {
	return m_vAsteroids;
}
