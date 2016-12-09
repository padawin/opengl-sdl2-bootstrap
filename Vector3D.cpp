#include "Vector3D.hpp"
#include <math.h>

Vector3D::Vector3D() {
	m_iX = 0;
	m_iY = 0;
	m_iZ = 0;
}

Vector3D::Vector3D(const float x, const float y, const float z) {
	m_iX = x;
	m_iY = y;
	m_iZ = z;
}

float Vector3D::getLength() {
	return sqrtf(powf(m_iX, 2.0) + powf(m_iY, 2.0) + powf(m_iZ, 2.0));
}

float Vector3D::getX() {
	return m_iX;
}
float Vector3D::getY() {
	return m_iY;
}
float Vector3D::getZ() {
	return m_iZ;
}

void Vector3D::setX(const float x) {
	m_iX = x;
}

void Vector3D::setY(const float y) {
	m_iY = y;
}

void Vector3D::setZ(const float z) {
	m_iZ = z;
}

void Vector3D::set(Vector3DCoord coord, const float value) {
	if (coord == VECTOR_X) {
		setX(value);
	}
	else if (coord == VECTOR_Y) {
		setY(value);
	}
	else if (coord == VECTOR_Z) {
		setZ(value);
	}
}

void Vector3D::normalize() {
	float l = getLength();
	if (l > 0) { // we never want to attempt to divide by 0
		(*this) *= 1 / l;
	}
}

// Vector operations

Vector3D Vector3D::operator+(const Vector3D& v2) const {
	return Vector3D(m_iX + v2.m_iX, m_iY + v2.m_iY, m_iZ + v2.m_iZ);
}

Vector3D Vector3D::operator-(const Vector3D& v2) const {
	return Vector3D(m_iX - v2.m_iX, m_iY - v2.m_iY, m_iZ - v2.m_iZ);
}

Vector3D Vector3D::operator*(float scalar) {
	return Vector3D(m_iX * scalar, m_iY * scalar, m_iZ * scalar);
}

Vector3D Vector3D::operator/(float scalar) {
	return Vector3D(m_iX / scalar, m_iY / scalar, m_iZ / scalar);
}

Vector3D& operator+=(Vector3D& v1, const Vector3D& v2) {
	v1.m_iX += v2.m_iX;
	v1.m_iY += v2.m_iY;
	v1.m_iZ += v2.m_iZ;
	return v1;
}

Vector3D& operator-=(Vector3D& v1, const Vector3D& v2) {
	v1.m_iX -= v2.m_iX;
	v1.m_iY -= v2.m_iY;
	v1.m_iZ -= v2.m_iZ;
	return v1;
}

Vector3D& operator*=(Vector3D& v1, float scalar) {
	v1.m_iX *= scalar;
	v1.m_iY *= scalar;
	v1.m_iZ *= scalar;
	return v1;
}

Vector3D& operator/=(Vector3D& v1, float scalar) {
	v1.m_iX /= scalar;
	v1.m_iY /= scalar;
	v1.m_iZ /= scalar;
	return v1;
}
