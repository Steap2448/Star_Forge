#include "celestial_body.hpp"

//Vector section
Vector::Vector()
{
	x = 0;
	y = 0;
}

Vector::Vector(double a, double b)
{
	x = a;
	y = b;
}

void Vector::set()
{
	x = 0;
	y = 0;
}

void Vector::set(double a)
{
	x = a;
}

void Vector::set(double a, double b)
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

double Vector::abs(Vector a)
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
Phase_vector::Phase_vector(double a, double b, double c, double d)
{
	x = a;
	y = b;
	v_x = c;
	v_y = d;
}

Phase_vector::Phase_vector(double a, double b)
{
	x = a;
	y = b;
	v_x = 0;
	v_y = 0;
}
Phase_vector Phase_vector::operator *(double a)
{
	Phase_vector res = Phase_vector();
	res.x = x * a;
	res.y = y * a;
	res.v_x = v_x * a;
	res.v_y = v_y * a;
	return res;
}
Phase_vector Phase_vector::operator /(double a)
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
	texture_path = "";
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

Celestial_Body::Celestial_Body(double a, double b, double c, double d, double e, double f, double g, double k, std::string t)//добавленный конструктор
{
	x = a;
	y = b;
	v_x = c;
	v_y = d;
	w_x = e;
	w_y = f;
	Radius = g;
	Mass = k;
	texture_path = t;
}

Celestial_Body::Celestial_Body(double a, double b, double c, double d, double e, double f, double g, double k)
{
	x = a;
	y = b;
	v_x = c;
	v_y = d;
	w_x = e;
	w_y = f;
	Radius = g;
	Mass = k;
	texture_path = "";
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

Celestial_Body Celestial_Body::operator +=(Phase_vector a)
{
	x+=a.x;
	y+=a.y;
	v_x+=a.v_x;
	v_y+=a.v_y;
	return *this;
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

Celestial_Body Celestial_Body::operator =(Celestial_Body a)
{
	x = a.x;
	y = a.y;
	v_x = a.v_x;
	v_y = a.v_y;
	Radius = a.Radius;
	Mass = a.Mass;
	return *this;
}

Celestial_Body Celestial_Body::operator =(Celestial_Body *a) //added by Nestor
{
	x = a->x;
	y = a->y;
	v_x = a->v_x;
	v_y = a->v_y;
	Radius = a->Radius;
	Mass = a->Mass;  
	texture_path = a->texture_path;
	return *this;
}

/*int Celestial_Body::operator ==(Celestial_Body a)
{
	if ((x == a.x)&&(y == a.y)&&(v_x == a.v_x)&&(v_y == a.v_y)&&(w_y == a.w_y)&&(w_y == a.w_y)&&(Radius == a.Radius)&&(Mass == a.Mass))
	return true;
	else return false;
}
int Celestial_Body::operator !=(Celestial_Body a)
{
	if ((x != a.x)||(y != a.y)||(v_x != a.v_x)||(v_y != a.v_y)||(w_y != a.w_y)||(w_y != a.w_y)||(Radius != a.Radius)||(Mass != a.Mass))
	return true;
	else return false;
}*/

//Atlas section

Atlas::Atlas()
{
	first = NULL;
	last = NULL;
	amount = 0;
}

Atlas::Atlas(Celestial_Body a)
{
	Atlas_node tmp = new Atlas_node_el;
	tmp->body = a;
	tmp->next = NULL;
	sf::CircleShape avat(a.Radius);
	tmp->avatar = avat;
	first = tmp;
	last = tmp;
	amount = 1;
}

void Atlas::add(Celestial_Body* a) //changed by Nestor
{
	Atlas_node tmp = new Atlas_node_el;
	tmp->body = a;
	tmp->next = NULL;
	sf::CircleShape avat(a->Radius);
	avat.setOrigin(a->Radius,a->Radius);
	tmp->avatar = avat;
	if(last != NULL)
	{
	last->next = tmp;
	last = last -> next;
	}
	else
	{
		last = tmp;
		first = tmp;
	}
	amount++;
	return;
}

/*void Atlas::remove(Celestial_Body* a)
{
	Celestial_Body* tmp = first, tmp2;
	if (first == a)
	{
		first = first->next;
		free(tmp);
		return;
	}
	while (tmp != NULL)
	{
		if(tmp->next == a)
		{
			tmp2 = tmp->next;
			tmp->next = tmp->next->next;
			free(tmp2);
		}
	}
}*/

void Atlas::del()
{
	Atlas_node tmp1 = first; 
	while (tmp1 != NULL)
	{
		Atlas_node tmp2 = tmp1;
		tmp1 = tmp1->next;
		delete(tmp2);
	}
}

void Atlas::out()
{
	Atlas_node tmp1 = first; 
	while (tmp1 != NULL)
	{
		std::cout<<"Atlas "<<tmp1->body<<"\n";
		tmp1 = tmp1->next;
	}
	return;
}





















