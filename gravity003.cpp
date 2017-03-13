#include <SFML/Graphics.hpp>
#include <iostream> 
#include <cmath>
//#include <Mouse.hpp>
using namespace sf;

class Object
{
	public:
	float r;
	float m;
	Vector2f velocity;
	Vector2i position;
	Object (float r1,float m1,Vector2i position1)
	{
		r=r1;
		m=m1;
		position=position1;
	}
	Object setobject(float r1,float m1,Vector2i position1)
	{
		r=r1;
		m=m1;
		position=position1;
	}
};

void flight(Object *o1,Object *o2,CircleShape *obj1,CircleShape *obj2)
{
	o1->position.x=obj1->getPosition().x;
	o1->position.y=obj1->getPosition().y;
	o2->position.x=obj2->getPosition().x;
	o2->position.y=obj2->getPosition().y;
	o1->velocity.x=-o2->m/(pow(o1->position.x-o2->position.x,2)+pow(o1->position.y-o2->position.y,2))*((o1->position.x-o2->position.x)/(sqrt(pow(o1->position.x-o2->position.x,2)+pow(o1->position.y-o2->position.y,2))));
	o1->velocity.y=-o2->m/(pow(o1->position.x-o2->position.x,2)+pow(o1->position.y-o2->position.y,2))*((o1->position.y-o2->position.y)/(sqrt(pow(o1->position.x-o2->position.x,2)+pow(o1->position.y-o2->position.y,2))));
	obj1->move(o1->velocity.x*1000,o1->velocity.y*1000);
	std::cout<<"o1->position.x="<<o1->position.x<<"\n"<<"o1->position.y="<<o1->position.y<<"\n"<<"o1->velocity.x="<<o1->velocity.x*10000<<"\n"<<"o1->velocity.y="<<o1->velocity.y*10000<<"\n";
}

int main()
{
	Object o1(0,0,Vector2i(0,0)),o2(0,0,Vector2i(0,0));
	Vector2i p;
	ConvexShape shape;
	shape.setPointCount(4);
	shape.setPoint(0, sf::Vector2f(0, 0));
	shape.setPoint(1, sf::Vector2f(10, 20));
	shape.setPoint(2, sf::Vector2f(10, 10));
	shape.setPoint(3, sf::Vector2f(20, 10));
	int i=0,j=0;
	float r1,r2,m1,m2;
	std::cin>>r1>>r2>>m1>>m2;
	RectangleShape cube(Vector2f(10,10));
	CircleShape Star(r1*20);
	CircleShape Planet(r2*5);
	Star.setOrigin(r1*20,r1*20);
	Planet.setOrigin(r2*5,r2*5);
	Star.setFillColor(Color::Yellow);
	Planet.setFillColor(Color::Blue);
	RenderWindow window(VideoMode(1920,1080),"test");
	window.setMouseCursorVisible(false);
	while (window.isOpen()) 
	{
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			i=1;
			o1.setobject(r1,m1,Mouse::getPosition());
			Star.setPosition(o1.position.x,o1.position.y);
		}
		if (Mouse::isButtonPressed(Mouse::Right))
		{
			j=1;
			o2.setobject(r2,m2,Mouse::getPosition());
			Planet.setPosition(o2.position.x,o2.position.y);
		}
	    if(i==1&&j==1&&(sqrt(pow(o1.position.x-o2.position.x,2)+pow(o1.position.y-o2.position.y,2))>r1*20+r2*5))
		{
			flight(&o1,&o2,&Star,&Planet);
			flight(&o2,&o1,&Planet,&Star);
		}
		p=Mouse::getPosition();
		shape.setPosition(p.x,p.y);
		Event event;
		while (window.pollEvent(event))
		{
			if(event.type == Event::KeyPressed && event.key.code == Keyboard::P) o1.velocity.x=100;
			if(event.type == Event::Closed || 
			(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
			window.close();
		}
		window.clear();
		if(i) window.draw(Star);
		if(j) window.draw(Planet);
		window.draw(cube);
		window.draw(shape);
		window.display();
	}
	return 0;
}
