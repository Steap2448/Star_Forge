#ifndef CELESTIAL_BODY
#define CELESTIAL_BODY

#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;

class Vector
{
	public:
	float x;
	float y;
	Vector();
	Vector(float a, float b);
	void set();
	void set(float x);
	void set(float x, float y);
	
	Vector operator +=(Vector a)
	{
		x += a.x;
		y += a.y;
	}
	
	Vector operator -=(Vector a)
	{
		x -= a.x;
		y -= a.y;
	}
	
	Vector operator +(Vector b);
	Vector operator -(Vector b);
	
	float abs(Vector a); //возвращает квадрат модуля 
	
/////////////////////////////////////Секция ввода/вывода
	friend std::ostream& operator<<(std::ostream& os, Vector& a)
	{
		os<<"("<<a.x<<","<<a.y<<")";
		return os;
	}
	
	friend std::istream& operator>>(std::istream& os, Vector& a)
	{
		float c, b;
		os>>c;
		os>>b;
		a.x = c;
		a.y = b;
		return os;
	}
};

class Phase_vector: public Vector
{
	public:
	float v_x;
	float v_y;
	Phase_vector();
	Phase_vector(float a, float b);
	Phase_vector(float a, float b, float c, float d);
	Phase_vector operator *(float a);
	Phase_vector operator /(float a);
	Phase_vector operator +(Phase_vector a);
	Phase_vector operator -(Phase_vector a);
	/////////////////////////////////////Секция ввода/вывода
	friend std::ostream& operator<<(std::ostream& os, Phase_vector& a)
	{
		os<<"("<<a.x<<","<<a.y<<","<<a.v_x<<","<<a.v_y<<")\n";
		return os;
	}
	
	friend std::istream& operator>>(std::istream& os, Phase_vector& a)
	{
		float c, b, f, g;
		os>>c;
		os>>b;
		os>>f;
		os>>g;
		a.x = c;
		a.y = b;
		a.v_x=f;
		a.v_y=g;
		return os;
	}
};

/////////////////////////////////////////////Celestial Body class is an expansion of Phase_vector class
class Celestial_Body: public Phase_vector
{
	public:
	float w_x;
	float w_y;
	float Radius;
	float Mass;
	Color color;
	Texture texture;
	Celestial_Body();
	Celestial_Body(const Celestial_Body& other);
	Celestial_Body(float a, float b, float c, float d, float e, float f, float g, float k); 
	Celestial_Body operator =(Celestial_Body a);
	Celestial_Body operator +(Phase_vector a);
	Celestial_Body operator -(Phase_vector a);
	int operator ==(Celestial_Body a);
	int operator !=(Celestial_Body a);
	friend std::ostream& operator<<(std::ostream& os, Celestial_Body& a)
	{
		os<<"("<<a.x<<","<<a.y<<","<<a.v_x<<","<<a.v_y<<")\n";
		return os;
	}
	void Move(float t_scale, Phase_vector k1, Phase_vector k2, Phase_vector k3, Phase_vector k4);
};

typedef struct _Atlas_node
{
	Celestial_Body body;
	CircleShape avatar;
	_Atlas_node* next;
} *Atlas_node, Atlas_node_el;

class Atlas
{
	public:
	Atlas_node first;
	Atlas_node last;
	int amount;
	Atlas();
	Atlas(Celestial_Body a);
	void add(Celestial_Body a);
	//void remove(Celestial_Body a);
	void del();
	void draw(RenderWindow window);
	void move();
};




#endif 
