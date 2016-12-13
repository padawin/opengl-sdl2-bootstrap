#ifndef __ENTITY__
#define __ENTITY__

#include "Vector3D.hpp"
#include "ShapeFactory.hpp"

class Entity {
	protected:
	Vector3D m_VAcceleration, m_VSpeed, m_VPosition;
	Vector3D m_VAngularAcceleration, m_VAngularSpeed, m_VAngle;
	Vector3D m_VCenter;

	public:
	void setCenter(Vector3D center);
	void setAcceleration(Vector3D acceleration);
	void setSpeed(Vector3D speed);
	void setPosition(Vector3D position);
	void setAngularAcceleration(Vector3D acceleration);
	void setAngularSpeed(Vector3D speed);
	void setAngle(Vector3D angle);
	Vector3D getCenter();
	Vector3D getAcceleration();
	Vector3D getSpeed();
	Vector3D getPosition();
	Vector3D getAngularAcceleration();
	Vector3D getAngularSpeed();
	Vector3D getAngle();
	virtual ShapeType getShapeType() = 0;
};

#endif
