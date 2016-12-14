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

void Entity::setDirection(Vector3D direction) {
	m_VDirection = direction;
	m_VDirection.normalize();
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

Vector3D Entity::getDirection() {
	return m_VDirection;
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

void Entity::update() {
	m_VSpeed += m_VAcceleration;
	m_VPosition += m_VSpeed;
	m_VAngularSpeed += m_VAngularAcceleration;
	m_VAngle += m_VAngularSpeed;
}

glm::mat4 Entity::getTransformationMatrix() {
	glm::mat4 trans;
	trans = glm::translate(
		trans,
		glm::vec3(m_VCenter.getX(), m_VCenter.getY(), m_VCenter.getZ())
	);
	trans = glm::translate(
		trans,
		glm::vec3(m_VPosition.getX(), m_VPosition.getY(), m_VPosition.getZ())
	);
	trans = glm::rotate(
		trans,
		glm::radians(m_VAngle.getX()),
		glm::vec3(1.0f, 0.0f, 0.0f)
	);
	trans = glm::rotate(
		trans,
		glm::radians(m_VAngle.getY()),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
	trans = glm::rotate(
		trans,
		glm::radians(m_VAngle.getZ()),
		glm::vec3(0.0f, 0.0f, 1.0f)
	);
	trans = glm::translate(
		trans,
		glm::vec3(-m_VCenter.getX(), -m_VCenter.getY(), -m_VCenter.getZ())
	);

	return trans;
}
