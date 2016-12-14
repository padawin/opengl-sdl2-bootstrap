#include "Player.hpp"
#include "ShapeFactory.hpp"
#include <math.h>

#define ACCELERATION_COEFFICIENT 0.002

ShapeType Player::getShapeType() {
	return SHIP;
}

void Player::update() {
	Entity::update();

	if (m_fSteerAngle != 0.0f) {
		_updateDirection();
	}
}

void Player::_updateDirection() {
	Vector3D direction = getDirection();
	float directionAngleZ = atan2(direction.getY(), direction.getX()) * 180 / M_PI;
	float angle = directionAngleZ + m_fSteerAngle;
	if (angle < 0.0f) {
		angle += 360.0f;
	}
	if (angle > 360.0f) {
		angle -= 360.0f;
	}
	angle = angle * M_PI / 180;
	setDirection(Vector3D(cos(angle), sin(angle), 0.0f));
}

void Player::thrust(bool activate) {
	setAcceleration(activate ? getDirection() * ACCELERATION_COEFFICIENT : Vector3D());
}

void Player::reverseThrust(bool activate) {
	setAcceleration(activate ? getDirection() * -ACCELERATION_COEFFICIENT : Vector3D());
}

void Player::_steer(float angle) {
	setAngularSpeed(Vector3D(0.0f, 0.0f, angle));
	m_fSteerAngle = angle;
}

void Player::steerLeft(bool activate) {
	//angle is in degrees
	_steer(activate ? 2.0f : 0.0f);
}

void Player::steerRight(bool activate) {
	_steer(activate ? -2.0f : 0.0f);
}
