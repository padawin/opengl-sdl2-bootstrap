#include "Player.hpp"
#include "ShapeFactory.hpp"

#define ACCELERATION_COEFFICIENT 0.002

ShapeType Player::getShapeType() {
	return SHIP;
}

void Player::thrust(bool activate) {
	setAcceleration(activate ? getDirection() * ACCELERATION_COEFFICIENT : Vector3D());
}

void Player::reverseThrust(bool activate) {
	setAcceleration(activate ? getDirection() * -ACCELERATION_COEFFICIENT : Vector3D());
}
