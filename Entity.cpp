#include "Entity.hpp"

void Entity::setCenter(Vector3D center) {
	m_VCenter = center;
}

void Entity::setAcceleration(Vector3D acceleration) {
	m_VAcceleration = acceleration;
}

void Entity::setSpeed(Vector3D speed) {
	m_VSpeed = speed;
}

void Entity::setPosition(Vector3D position) {
	m_VPosition = position;
}

void Entity::setAngularAcceleration(Vector3D acceleration) {
	m_VAngularAcceleration = acceleration;
}

void Entity::setAngularSpeed(Vector3D speed) {
	m_VAngularSpeed = speed;
}

void Entity::setAngle(Vector3D angle) {
	m_VAngle = angle;
}

Vector3D Entity::getCenter() {
	return m_VCenter;
}

Vector3D Entity::getAcceleration() {
	return m_VAcceleration;
}

Vector3D Entity::getSpeed() {
	return m_VSpeed;
}

Vector3D Entity::getPosition() {
	return m_VPosition;
}

Vector3D Entity::getAngularAcceleration() {
	return m_VAngularAcceleration;
}

Vector3D Entity::getAngularSpeed() {
	return m_VAngularSpeed;
}

Vector3D Entity::getAngle() {
	return m_VAngle;
}
