#ifndef CELESTIAL_BODY
#define CELESTIAL_BODY

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
	
	void operator +=(Vector a)
	{
		x += a.x;
		y += a.y;
		return;
	}
	
	void operator -=(Vector a)
	{
		x -= a.x;
		y -= a.y;
		return;
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
	Phase_vector mov;
	std::string texture_path;
	std::string body_name;
	sf::Color color;
	sf::Texture t;
	Celestial_Body();
	Celestial_Body(const Celestial_Body& other);
	Celestial_Body(double a, double b, double c, double d, double e, double f, double g, double k); 
	Celestial_Body(double a, double b, double c, double d, double e, double f, double g, double k, std::string t,std::string name);
	Celestial_Body operator =(Celestial_Body a);
	Celestial_Body operator =(Celestial_Body* a);
	Celestial_Body operator +(Phase_vector a);
	Celestial_Body operator +=(Phase_vector a);
	Celestial_Body operator -(Phase_vector a);
	int operator ==(Celestial_Body a);
	int operator !=(Celestial_Body a);
	void satellite_of(Celestial_Body* a);
	friend std::ostream& operator<<(std::ostream& os, Celestial_Body& a)
	{
		os<<"("<<a.x<<","<<a.y<<","<<a.v_x<<","<<a.v_y<<")\n";
		return os;
	}
};

typedef struct _Atlas_node
{
	Celestial_Body body;
	sf::CircleShape avatar;
	_Atlas_node* next;
} *Atlas_node, Atlas_node_el;

double x(double x_m, double scale);

double y(double y_m, double scale);

double x(double x_m, double scale,double aph,double b);

double y(double y_m, double scale,double aph,double b);

double x(double x_m, double scale,double aph, sf::Vector2i p,double b);

double y(double y_m, double scale,double aph, sf::Vector2i p,double b);

double x(double x_m, double scale,double aph, sf::Vector2i p,double b, Atlas_node target);

double y(double x_m, double scale,double aph, sf::Vector2i p,double b, Atlas_node target);

double x_satellite(double x, Celestial_Body* a);

double y_satellite(double y, Celestial_Body* a);

double v_x_satellite(double v_x, Celestial_Body* a);

double v_y_satellite(double v_y, Celestial_Body* a);

class Atlas
{
	public:
	std::string name;
	Atlas_node first;
	Atlas_node last;
	Atlas_node active;
	Atlas_node active2;
	int amount;
	Atlas();
	Atlas(Celestial_Body a);
	void add(Celestial_Body* a);
	void remove();
	void del();
	void draw(sf::RenderWindow window);
	void move(double scale);
	void out();
	double get_max();
	sf::Vector2i mass_center(double scale ,double aph,double b);
	double get_max(sf::Vector2i mass_center); //This is new
	double get_medium();
	double get_medium(sf::Vector2i mass_center);
};

void draw(Atlas* atl, sf::RenderWindow* window);



#endif 
