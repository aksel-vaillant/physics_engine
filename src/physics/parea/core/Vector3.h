#include <ostream>
#include "Precision.h"

class Vector3 {
public:
	real x;
	real y;
	real z;

public:
	/******* DEFAULT CONSTUCTOR *******/
	Vector3() : x(0), y(0), z(0) {}
	/******* EXPLICIT CONSTUCTOR *******/	
	Vector3(const real x) : x(x), y(x), z(x) {}
	Vector3(const real x, const real y, const real z) : x(x), y(y), z(z) {}
	/******* CLEAR *******/
	void clear() {
		x = 0;
		y = 0;
		z = 0;
	}
	/******* FLIP ALL COMPONENTS OF THE VECTOR *******/
	void invert() {
		x = -x;
		y = -y;
		z = -z;
	}
	/******* VECTOR AND DIRECTION *******/
	real magnitude() const {
		return (real)sqrt(x * x + y * y + z * z);
	}
	real squareMagnitude() const {
		return x * x + y * y + z * z;
	}
	void normalize() {
		real l = magnitude();
		if (l > 0) {
			(*this) *= ((real)1) / l;
		}
	}
	/******* SCALAR AND VECTOR MULTIPLICATION *******/
	void operator*=(const real value) {
		x *= value;
		y *= value;
		z *= value;
	}
	Vector3 operator*(const real value) const {
		return Vector3(x * value, y * value, z * value);
	}
	/******* VECTOR ADDITION *******/
	void operator+=(const Vector3& v) {
		x += v.x;
		y += v.y;
		z += v.z;
	}
	Vector3 operator+(const Vector3& v) const {
		return Vector3(x + v.x, y + v.y, z + v.z);
	}
	/******* VECTOR SUBTRACTION *******/
	void operator-=(const Vector3& v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
	}
	Vector3 operator - (const real s) const {
		return Vector3(x - s, y - s, z - s);
	}

	Vector3 operator - (const Vector3& v) const {
		return Vector3(x - v.x, y - v.y, z - v.z);
	}
	/******* VECTOR ADDITION AND SCALING *******/
	void addScaledVector(const Vector3& v, real scale) {
		x += v.x * scale;
		y += v.y * scale;
		z += v.z * scale;
	}
	/******* COMPONENT PRODUCT *******/
	void componentProductUpdate(const Vector3& v) {
		x *= v.x;
		y *= v.y;
		z *= v.z;
	}
	Vector3 componentProduct(const Vector3& v) const {
		return Vector3(x * v.x, y * v.y, z * v.z);
	}
	/******* SCALAR PRODUCT *******/
	real scalarProduct(const Vector3& v) const {
		return x * v.x + y * v.y + z * v.z;
	}
	real operator*(const Vector3& v) const {
		return x * v.x + y * v.y + z * v.z;
	}
	/******* VECTOR PRODUCT *******/
	Vector3 vectorProduct(const Vector3& v) const {
		return Vector3(y * v.z - z * v.y,
			z * v.x - x * v.z,
			x * v.y - y * v.x);
	}
	void operator%=(const Vector3& v) {
		(*this) = vectorProduct(v);
	}
	Vector3 operator%(const Vector3& v) const {
		return Vector3(y * v.z - z * v.y,
			z * v.x - x * v.z,
			x * v.y - y * v.x);
	}
	/******* ORTHONORMAL BASIS *******/
	void makeOrthonormalBasis(Vector3* a, Vector3* b, Vector3* c) {
		a->normalize();
		(*c) = (*a) % (*b);
		if (c->squareMagnitude() == 0.0) {
			return;
		}
		c->normalize();
		(*b) = (*c) % (*a);
	}
	/******* PRINTING FUNCTION *******/
	friend std::ostream& operator << (std::ostream& os, const Vector3& vector) {
		return os << "Vector3 : x=" << vector.x << "\t\ty=" << vector.y << "\t\tz=" << vector.z;
	}
};