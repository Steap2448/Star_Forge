#include <iostream>
#include "celestial_body.h"
using namespace std;

//Vector section
Vector::Vector()
{
	x = 0;
	y = 0;
}

Vector::Vector(float a, float b)
{
	x = a;
	y = b;
}

void Vector::set()
{
	x = 0;
	y = 0;
}

void Vector::set(float a)
{
	x = a;
}

void Vector::set(float a, float b)
{
	x = a;
	y = b;
}

Vector Vector::operator +(Vector b)
{
	Vector c;
	c.x = x + b.x;
	c.y = y + b.y;
	return c;
}

Vector Vector::operator -(Vector b)
{
	Vector c;
	c.x = x - b.x;
	c.y = y - b.y;
	return c;
}

float Vector::abs(Vector a)
{
	return (a.x * a.x)+(a.y * a.y);
}
//Phase_vector section
Phase_vector::Phase_vector()
{
	x = 0;
	y = 0;
	v_x = 0;
	v_y = 0;
}
Phase_vector::Phase_vector(float a, float b, float c, float d)
{
	x = a;
	y = b;
	v_x = c;
	v_y = d;
}

Phase_vector::Phase_vector(float a, float b)
{
	x = a;
	y = b;
	v_x = 0;
	v_y = 0;
}
Phase_vector Phase_vector::operator *(float a)
{
	Phase_vector res = Phase_vector();
	res.x = x * a;
	res.y = y * a;
	res.v_x = v_x * a;
	res.v_y = v_y * a;
	return res;
}
Phase_vector Phase_vector::operator /(float a)
{
	Phase_vector res = Phase_vector();
	res.x = x / a;
	res.y = y / a;
	res.v_x = v_x / a;
	res.v_y = v_y / a;
	return res;
}
Phase_vector Phase_vector::operator +(Phase_vector a)
{
	Phase_vector res = Phase_vector();
	res.x = x + a.x;
	res.y = y + a.y;
	res.v_x = v_x + a.v_x;
	res.v_y = v_y + a.v_y;
	return res;
}
Phase_vector Phase_vector::operator -(Phase_vector a)
{
	Phase_vector res = Phase_vector();
	res.x = x - a.x;
	res.y = y - a.y;
	res.v_x = v_x - a.v_x;
	res.v_y = v_y - a.v_y;
	return res;
}
//Celestial_body section
Celestial_Body::Celestial_Body()
{
	x = 0;
	y = 0;
	v_x = 0;
	v_y = 0;
	w_x = 0;
	w_y = 0;
	Radius = 0;
	Mass = 0;
}

Celestial_Body::Celestial_Body(const Celestial_Body& other)
{
	x = other.x;
	y = other.y;
	v_x = other.v_x;
	v_y = other.v_y;
	w_x = other.w_x;
	w_y = other.w_y;
	Radius = other.Radius;
	Mass = other.Mass;
}

Celestial_Body::Celestial_Body(float a, float b, float c, float d, float e, float f, float g, float k)
{
	x = a;
	y = b;
	v_x = c;
	v_y = d;
	w_x = e;
	w_y = f;
	Radius = g;
	Mass = k;
}

Celestial_Body Celestial_Body::operator +(Phase_vector a)
{
	Celestial_Body res = Celestial_Body(x, y, v_x, v_y, w_x, w_y, Radius, Mass);
	res.x+=a.x;
	res.y+=a.y;
	res.v_x+=a.v_x;
	res.v_y+=a.v_y;
	return res;
}

Celestial_Body Celestial_Body::operator -(Phase_vector a)
{
	Celestial_Body res = Celestial_Body(x, y, v_x, v_y, w_x, w_y, Radius, Mass);
	res.x-=a.x;
	res.y-=a.y;
	res.v_x-=a.v_x;
	res.v_y-=a.v_y;
	return res;
}

