#ifndef __PLAYER__
#define __PLAYER__

#include "Entity.hpp"

class Player : public Entity {
	private:
	void _steer(float angle);
	void _updateDirection();
	float m_fSteerAngle = 0.0f;

	public:
	ShapeType getShapeType();
	void thrust(bool activate);
	void reverseThrust(bool activate);
	void steerLeft(bool activate);
	void steerRight(bool activate);
	void update();
};

#endif
