#define WIDTH 600
#define T_SCALE 10

#include "celestial_body.h"
#include <SFML/Graphics.hpp>
#include <iostream> 
#include "method.cpp"
#include "celestial_body.cpp"
using namespace sf;
int main()
{
	Clock clock; 
	RenderWindow window(VideoMode(WIDTH,WIDTH),"test");
	Celestial_Body Sun(0,0,0,0,0,0,40,1.9885e30), Earth(1.521e11,0,0,29.783e3,0,0,2,5.9726e24), Mars(50.005 , 284.005, 0, 0, 0, 0, 2, 0.01);
	CircleShape Star(Sun.Radius);
	CircleShape Planet(Earth.Radius);
	CircleShape Planet2(2);	
	Star.setOrigin(5,5);
	Planet.setOrigin(2,2);
	Star.setFillColor(Color::Yellow);
	Planet.setFillColor(Color::Blue);
	Planet2.setFillColor(Color::Red);
	Star.setPosition(x(Sun.x, WIDTH),x(Sun.y, WIDTH));
	Planet.setPosition(x(Earth.x, WIDTH),y(Earth.y, WIDTH));
	//Planet2.setPosition(Mars.x,Mars.y);
	Phase_vector v1,v2;
	while (window.isOpen()) 
	{
		float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
		clock.restart(); //перезагружает время
		time = T_SCALE * time;	
		v1=Movement(Sun,Earth,time);
		v2=Movement(Earth,Sun,time);
		Sun=Sun+v1;
		Earth=Earth+v2;
		Star.setPosition(x(Sun.x, WIDTH),x(Sun.y, WIDTH));
	    Planet.setPosition(x(Earth.x, WIDTH),y(Earth.y, WIDTH));
		Event event;
		while (window.pollEvent(event))
		{
			if(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			window.close();
		}
		cout<<v2;
		window.clear();
		window.draw(Star);
		window.draw(Planet);
		//window.draw(Planet2);
		window.display();
	}
return 0;
}
