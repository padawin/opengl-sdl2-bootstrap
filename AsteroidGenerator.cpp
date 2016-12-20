#include "AsteroidGenerator.hpp"
#include <math.h>

void AsteroidGenerator::setDistanceRecycle(float distance) {
	m_fDistanceRecycle = distance;
}

void AsteroidGenerator::setRangeDistanceAppear(unsigned int minDistance, unsigned int maxDistance) {
	m_iMinDistanceAppear = minDistance;
	// multiplication because rand returns an int, so the returned value will
	// then be divided by 1000.0f
	m_iMaxDistanceAppear = maxDistance * 1000;
}

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

	float speed = (rand() % 1000) / 10000.0f;
	float angle = (rand() % 360) * M_PI / 180;
	asteroid->setAngularSpeed(
		Vector3D(angularSpeedX, angularSpeedY, angularSpeedZ)
	);
	asteroid->setSpeed(Vector3D(
		speed * cos(angle),
		speed * sin(angle),
		0.0f
	));
	m_vAsteroids.push_back(asteroid);
}

void AsteroidGenerator::update(Vector3D thresholdPosition) {
	for (std::vector<Entity*>::size_type i = 0; i < m_vAsteroids.size(); ++i) {
		Vector3D distance = m_vAsteroids.at(i)->getPosition() - thresholdPosition;
		if (distance.getLength() > m_fDistanceRecycle) {
			_removeAsteroid(i);
		}
	}

	_generateAsteroids(thresholdPosition);
}

void AsteroidGenerator::_generateAsteroids(Vector3D thresholdPosition) {
	if (m_vAsteroids.size() == NB_MAX_ASTEROIDS) {
		return;
	}

	int nbNewAsteroids = rand() % (NB_MAX_ASTEROIDS - m_vAsteroids.size());
	while (nbNewAsteroids--) {
		float distance, angle, x, y;
		distance = m_iMinDistanceAppear + (rand() % m_iMaxDistanceAppear) / 1000.0f;
		angle = (rand() % 360) * M_PI / 180;
		x = thresholdPosition.getX() + distance * cos(angle);
		y = thresholdPosition.getY() + distance * sin(angle);
		addAsteroid(Vector3D(x, y, 0.0f));
	}
}

void AsteroidGenerator::_removeAsteroid(unsigned int asteroidIndex) {
	free(m_vAsteroids[asteroidIndex]);
	m_vAsteroids[asteroidIndex] = m_vAsteroids.back();
	m_vAsteroids.pop_back();
}

void AsteroidGenerator::clean() {
	for (std::vector<Entity*>::size_type i = 0; i < m_vAsteroids.size(); ++i) {
		free(m_vAsteroids[i]);
	}
}

std::vector<Asteroid*> AsteroidGenerator::getAsteroids() {
	return m_vAsteroids;
}
