#ifndef VECTOR2F_H
#define VECTOR2F_H

#include <math.h> 

/*
	Move the class methods definitions to the cpp files and left the declarations in the header file
*/

class Vector2f
{
public:
	Vector2f();

	Vector2f(float anX, float anY);

	const Vector2f operator+(const Vector2f& other) const;
	const Vector2f operator-(const Vector2f& other) const;
	const Vector2f operator*(const Vector2f& other) const;
	
	Vector2f& operator+=(const Vector2f& other);
	Vector2f& operator-=(const Vector2f& other);
	Vector2f& operator*=(const Vector2f& other);
	Vector2f& operator*=(const float aFloat);
	Vector2f& operator/=(const float aFloat);

	// Scalar multiplication
	const Vector2f operator*(const float aValue) const;

	float Length() const;

	void Normalize();

	float myX;
	float myY;
};

#endif // VECTOR2F_H