#ifndef __Vector3D__
#define __Vector3D__

enum Vector3DCoord {VECTOR_X, VECTOR_Y, VECTOR_Z};

/**
 * Class to handle vectors. a vector is a distance between two points. It is
 * composed of a x and a y values.
 */
class Vector3D {
	protected:
	float m_iX = 0.0;
	float m_iY = 0.0;
	float m_iZ = 0.0;

	public:
	/**
	 * Default construct
	 */
	Vector3D();

	/**
	 * Construct providing the vector information.
	 */
	Vector3D(const float x, const float y, const float z);

	/**
	 * Different getters for the vector.
	 */
	float getLength();
	float getX();
	float getY();
	float getZ();

	/**
	 * Coord can be either VECTOR_X, VECTOR_Y or VECTOR_Z, depending it, the
	 * coordinate x, y or z of the vector with be set with value
	 */
	void set(Vector3DCoord coord, const float value);
	void setX(const float x);
	void setY(const float y);
	void setZ(const float z);

	/**
	 * Extands or reduce the x, y and z of the vector so its length is equal to 1.
	 */
	void normalize();

	// Vector operations
	Vector3D operator+(const Vector3D& v2) const;
	Vector3D operator-(const Vector3D& v2) const;
	Vector3D operator*(float scalar);
	Vector3D operator/(float scalar);

	friend Vector3D& operator+=(Vector3D& v1, const Vector3D& v2);
	friend Vector3D& operator-=(Vector3D& v1, const Vector3D& v2);
	friend Vector3D& operator*=(Vector3D& v, float scalar);
	friend Vector3D& operator/=(Vector3D& v, float scalar);
};

#endif
