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

Celestial_Body::Celestial_Body(double a, double b, double c, double d, double e, double f, double g, double k, std::string t, std::string name)//добавленный конструктор
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
	body_name = name;
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
	texture_path = "_";
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
	texture_path = a.texture_path;
	body_name = a.body_name;
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
	body_name = a->body_name;
	return *this;
}

void Celestial_Body::satellite_of(Celestial_Body* a)
{
	x = x_satellite(x, a);
	y = y_satellite(y, a);
	v_x = v_x_satellite(v_x, a);
	v_y = v_y_satellite(v_y, a);
	return;
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

double x(double x_m, double scale)
{
	double res = (x_m * (scale))/(6.084e11) + scale/2;
	return res;
}

double y(double y_m, double scale)
{
	double res = scale/2 - (y_m * scale)/(6.084e11);
	return res;
}

double x(double x_m, double scale,double aph,double b)
{
	double res = (x_m * (scale))/(4*b*aph) + scale/2;
	return res;
}

double y(double y_m, double scale,double aph,double b)
{
	double res = scale/2 - (y_m * scale)/(4*b*aph);
	return res;
}

double x(double x_m, double scale,double aph, sf::Vector2i p,double b)
{
	double res = (x_m * (scale))/(4*b*aph) + scale/2 - p.x;
	return res;
}

double y(double y_m, double scale,double aph, sf::Vector2i p,double b)
{
	double res = scale/2 - (y_m * scale)/(4*b*aph) - p.y;
	return res;
}

double x(double x_m, double scale,double aph, sf::Vector2i p,double b, Atlas_node target)
{
	if(target == NULL)
	{
		double res = (x_m * (scale))/(4*b*aph) + scale/2 - p.x;
		return res;
	}else
	{
		double res = ((x_m - target->body.x) * (scale))/(4*b*aph) + scale/2;
		return res;	
	}
}

double y(double y_m, double scale,double aph, sf::Vector2i p,double b, Atlas_node target)
{
	if(target == NULL)
	{
		double res = scale/2 - (y_m * (scale))/(4*b*aph) - p.y;
		return res;
	}else
	{
		double res = scale/2 - ((y_m - target->body.y) * (scale))/(4*b*aph) ;
		return res;	
	}
}

double x_satellite(double x, Celestial_Body* a)
{
	double res = x + a->x;
	return res;
}

double y_satellite(double y, Celestial_Body* a)
{
	double res = y + a->y;
	return res;
}

double v_x_satellite(double v_x, Celestial_Body* a)
{
	double res = v_x + a->v_x;
	return res;
}

double v_y_satellite(double v_y, Celestial_Body* a)
{
	double res = v_y + a->v_y;
	return res;
}

Atlas::Atlas()
{
	first = NULL;
	last = NULL;
	active = NULL;
	active2 = NULL;
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
	active = NULL;
	active2 = NULL;
	amount = 1;
}

void Atlas::add(Celestial_Body* a) //changed by Nestor
{
	if (active == NULL)
	{
		Atlas_node tmp = new Atlas_node_el;
		tmp->body = a;
		tmp->next = NULL;
		sf::CircleShape avat(a->Radius);
		avat.setOrigin(a->Radius,a->Radius);
		if(a->texture_path!="_")
		{
			tmp->body.t.loadFromFile(tmp->body.texture_path);
			avat.setTexture(&(tmp->body.t));
		}
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
		if (amount == 0) first = last = tmp;
		amount++;
		return;
	}else
	{
		Atlas_node tmp = new Atlas_node_el;
		a->satellite_of(&(active->body));
		tmp->body = a;
		tmp->next = NULL;
		sf::CircleShape avat(a->Radius);
		avat.setOrigin(a->Radius,a->Radius);
		if(a->texture_path!="_")
		{
			tmp->body.t.loadFromFile(tmp->body.texture_path);
			avat.setTexture(&(tmp->body.t));
		}
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
		active = NULL;
		return;
	}
}

double Atlas::get_max()
{
	if (amount == 0) return 0;
	if (amount == 1) return 1.5e11;
	double max = 0, k;
	Atlas_node tmp = first;
	while (tmp != NULL)
	{
		k = sqrt((tmp->body.x * tmp->body.x) + (tmp->body.y * tmp->body.y));
		if (k > max) max = k;
		tmp = tmp -> next;
	}
	return max;
}



/*void Atlas::remove()
{
		Atlas_node tmp = first;
		if (tmp == NULL) return;
		while (tmp -> next != active) tmp = tmp -> next;
		tmp -> next = active -> next;
		delete active;
		active = NULL;
	void remove()
	{
		object* tmp;
		object* ntr;
		tmp = first;
		if (tmp->eq == active)
		{
			if(tmp->next)set(tmp->next);
			tmp = first->next;
			delete first;
			first = tmp;
			if(counter == 1) first = NULL;
			active = NULL;
			counter--;
			return;
		}
		while (tmp->next && tmp->next->eq!=active)
		{
			tmp = tmp -> next;
		}
		if(tmp->next==last) last = tmp;
		if(tmp->next)
		{
			set(tmp->next);
			ntr=tmp->next;
		}
		else ntr->next = NULL;
		if (ntr->next) tmp->next=tmp->next->next;
		else tmp->next = NULL;
		delete ntr;
		counter--;
		active = NULL;
		sign = 0;
	}
}*/

void Atlas::remove()
{
	if (active == active2)
	active2 = NULL;
	if (active == NULL) return;
	Atlas_node tmp = first;
	if (first == active)
	{
		if (first == last)
		{
			delete active;
			first = NULL;
			last = NULL;
			amount = 0;
			active = 0;
			return;
		}
		first = first -> next;
		if (active -> next == NULL) last = tmp;
		active = NULL;
		delete tmp;
		amount--;
		return;
	}
	if (active == last)
	{
		if (first == last)
		{
			delete active;
			first = NULL;
			last = NULL;
			amount = 0;
			active = 0;
			return;
		}
		while (tmp->next != last) tmp = tmp -> next;
		tmp -> next = NULL;
		delete active;
		active = NULL;
		last = tmp;
		amount--;
		return;
	}
	while (tmp -> next != active) tmp = tmp -> next;
	tmp -> next = active -> next;
	if (active -> next == NULL) last = tmp;
	amount--;
	delete active;
	active = NULL;
	return; 
}

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
		tmp1 = tmp1->next;
	}
	return;
}

void draw(Atlas* atl, sf::RenderWindow* window)
{
	Atlas_node tmp = atl->first;
	while(tmp != NULL)
	{
		window->draw(tmp->avatar);
		tmp = tmp->next;
	}	
	return;
}



sf::Vector2i Atlas::mass_center(double scale,double aph,double b) //This is new
{
	sf::Vector2i tmp1(0, 0);
	sf::Vector2i res = tmp1;
	if (amount == 0) return res;
	if (amount == 1)
	{
		res.x = x(first->body.x, scale, aph, b)-scale/2;
		res.y = -scale/2+y(first->body.y, scale, aph, b);
		return res;
	}
	Atlas_node tmp = first;
	double res_x = 0, res_y = 0, res_mass = 0;
	while (tmp != NULL)
	{
		res_x += (tmp -> body.x) * (tmp -> body.Mass);
		res_y += (tmp -> body.y) * (tmp -> body.Mass);
		res_mass += tmp -> body.Mass;
		tmp = tmp -> next;
	}
	res.x = x(res_x/res_mass, scale, aph, b)-scale/2;
	res.y = -scale/2+y(res_y/res_mass, scale, aph, b);
	return res;	
}


double Atlas::get_max(sf::Vector2i mass_center)
{
	if (amount == 0) return 0;
	if (amount == 1) return 1.5e11;
	double max = 0, k;
	Atlas_node tmp = first;
	while (tmp != NULL)
	{
		k = sqrt(((tmp->body.x - mass_center.x) * (tmp->body.x - mass_center.x)) + ((tmp->body.y - mass_center.y) * (tmp->body.y - mass_center.y)));
		if (k > max) max = k;
		tmp = tmp -> next;
	}
	return max;
}

double Atlas::get_medium()
{
	if (amount == 0) return 0;
	if (amount == 1) return 1.5e11;
	double medium = 0, k;
	Atlas_node tmp = first;
	while (tmp != NULL)
	{
		medium += sqrt(((tmp->body.x) * (tmp->body.x)) + ((tmp->body.y) * (tmp->body.y)));
		tmp = tmp -> next;
	}
	
	medium = medium/amount;
	return medium;
}

double Atlas::get_medium(sf::Vector2i mass_center)
{
	if (amount == 0) return 0;
	if (amount == 1) return 1.5e11;
	double medium = 0;
	Atlas_node tmp = first;
	while (tmp != NULL)
	{
		medium += sqrt(((tmp->body.x - mass_center.x) * (tmp->body.x - mass_center.x)) + ((tmp->body.y - mass_center.y) * (tmp->body.y - mass_center.y)));
		tmp = tmp -> next;
	}
	
	medium = medium/amount;
	return medium;
}
















