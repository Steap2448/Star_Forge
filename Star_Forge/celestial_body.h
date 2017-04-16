#ifndef CELESTIAL_BODY
#define CELESTIAL_BODY

#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;

class Vector
{
	public:
	double x;
	double y;
	Vector();
	Vector(double a, double b);
	void set();
	void set(double x);
	void set(double x, double y);
	
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
	
	double abs(Vector a); //возвращает квадрат модуля 
	
/////////////////////////////////////Секция ввода/вывода
	friend std::ostream& operator<<(std::ostream& os, Vector& a)
	{
		os<<"("<<a.x<<","<<a.y<<")";
		return os;
	}
	
	friend std::istream& operator>>(std::istream& os, Vector& a)
	{
		double c, b;
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
	double v_x;
	double v_y;
	Phase_vector();
	Phase_vector(double a, double b);
	Phase_vector(double a, double b, double c, double d);
	Phase_vector operator *(double a);
	Phase_vector operator /(double a);
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
		double c, b, f, g;
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
	double w_x;
	double w_y;
	double Radius;
	double Mass;
	std::string texture_path;
	Color color;
	Texture texture;
	Celestial_Body();
	Celestial_Body(const Celestial_Body& other);
	Celestial_Body(double a, double b, double c, double d, double e, double f, double g, double k); 
	Celestial_Body(double a, double b, double c, double d, double e, double f, double g, double k, std::string t);
	Celestial_Body operator =(Celestial_Body a);
	Celestial_Body operator =(Celestial_Body* a);
	Celestial_Body operator +(Phase_vector a);
	Celestial_Body operator -(Phase_vector a);
	int operator ==(Celestial_Body a);
	int operator !=(Celestial_Body a);
	friend std::ostream& operator<<(std::ostream& os, Celestial_Body& a)
	{
		os<<"("<<a.x<<","<<a.y<<","<<a.v_x<<","<<a.v_y<<")\n";
		return os;
	}
	void Move(double t_scale, Phase_vector k1, Phase_vector k2, Phase_vector k3, Phase_vector k4);
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
	std::string name;
	Atlas_node first;
	Atlas_node last;
	int amount;
	Atlas();
	Atlas(Celestial_Body a);
	void add(Celestial_Body* a);
	//void remove(Celestial_Body a);
	void del();
	void draw(RenderWindow window);
	void move();
};




#endif 
