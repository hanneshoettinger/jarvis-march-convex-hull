#include "vector2.h"
#include <math.h>


Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2::Vector2()
{
	x = 0;
	y = 0;
}


Vector2::~Vector2()
{
}

void Vector2::operator+=(const Vector2 & rhs)
{
	x +=  rhs.x;
	y +=  rhs.y;
}

Vector2 Vector2::operator+(const Vector2 &rhs)
{
	Vector2 temp;
	temp.x = x + rhs.x;
	temp.y = y + rhs.y;
	return temp;
}
Vector2 Vector2::operator-(const Vector2 &rhs)
{
	Vector2 temp;
	temp.x = x - rhs.x;
	temp.y = y - rhs.y;
	return temp;
}
Vector2 Vector2::operator*(const float &rhs)
{
	Vector2 temp;
	temp.x = x * rhs;
	temp.y = y * rhs;
	return temp;
}

Vector2 Vector2::operator/(const float & rhs)
{
	Vector2 temp;
	temp.x = x / rhs;
	temp.y = y / rhs;
	return temp;
	return Vector2();
}

Vector2 Vector2::invert()
{
	Vector2 temp;
	temp.x = -x;
	temp.y = -y;
	return temp;
}

Vector2 Vector2::rotate(float angle)
{
	Vector2 temp;

	float theta = (angle*PI)/180;

	float cs = cos(theta);
	float sn = sin(theta);

	float px = x * cs - y * sn;
	float py = x * sn + y * cs;

	x = px;
	y = py;

	temp.x = x;
	temp.y = y;

	return temp;
}

Vector2 Vector2::Normalize()
{
	Vector2 temp;
	float length = this->Length();
	temp.x = x / length;
	temp.y = y / length;
	return temp;
}

float Vector2::Length()
{
	float result = sqrt(pow(this->x, 2) + pow(this->y, 2));
	return result;
}
float Vector2::AbsLength()
{
	float result = pow(this->x, 2) + pow(this->y, 2);
	return result;
}

float Vector2::GetAngle()
{
	float temp=atan2(y,x);
	return temp;
}
float Vector2::GetAbsDistance(const Vector2 &rhs)
{
	float temp;
	Vector2 tempv;
	tempv.x = this->x - rhs.x;
	tempv.y = this->y - rhs.y;
	temp = tempv.AbsLength();
	return temp;
}

Vector2 Vector2::rotate90()
{
	if (x > 0)		return Vector2(0 , 1);
	else if (x < 0) return Vector2(0 , -1);
	else if (y > 0) return Vector2(-1 , 0);
	else if (y < 0) return Vector2(1 , 0);
	return Vector2();
}
