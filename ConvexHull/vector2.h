#pragma once

#define PI 3.1415927410125732421875
class Vector2
{
public:
	Vector2(float,float);
	Vector2();
	~Vector2();
	void operator+=(const Vector2 &rhs);
	Vector2 operator+(const Vector2 &rhs);
	Vector2 operator-(const Vector2 &rhs);
	Vector2 operator*(const float &rhs);
	Vector2 operator/(const float &rhs);
	Vector2 invert();
	Vector2 rotate90();
	Vector2 rotate(float);
	Vector2 Normalize();
	float GetAbsDistance(const Vector2 &rhs);
	float Length();
	float AbsLength();
	float GetAngle();
public:
	float x;
	float y;
};