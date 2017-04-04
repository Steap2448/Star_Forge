#define WIDTH 600
#define T_SCALE 1

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
	Atlas atl;
	Celestial_Body Sun(0,0,0,0,0,0,5,1.9885e30), Earth(152.1e9,0,0,29.783e3,0,0,1,5.9726e24), Mars(206.62e9 , 0, 0, 26.50e3, 0, 0, 1, 0.64171e24);
	Celestial_Body Mercury(46e9, 0, 0, 58.98e3, 0, 0, 1, 0.33011e24), Venus(107.48e9, 0, 0, 35.26e3, 0, 0, 1, 4.8675e24);//, Jupiter(740.52e9, 0, 0, 13.72e3, 0, 0, 3, 1898.19e24);
	/*Atlas_node Sunn = new Atlas_node_el;
	Sunn->body = Sun;
	CircleShape sunav(Sun.Radius);
	Sunn->avatar = sunav;
	Atlas_node Earthn = new Atlas_node_el;
	Earthn->body = Earth;
	CircleShape earthav(Earth.Radius);
	Earthn->avatar = earthav;
	Sunn->next = Earthn;
	Earthn->next = NULL;
	atl.first = Sunn;
	atl.last = Earthn;
	atl.amount = 2;*/
	atl.add(Sun);
	atl.add(Earth);
	atl.add(Mars);	
	atl.add(Mercury);
	atl.add(Venus);
	//atl.add(Jupiter);
	//Planet2.setPosition(Mars.x,Mars.y);
	Phase_vector v1,v2;
	while (window.isOpen()) 
	{
		float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
		clock.restart(); //перезагружает время
		time = T_SCALE * time;	
		Motion(atl, time, WIDTH);
		Event event;
		while (window.pollEvent(event))
		{
			if(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			window.close();
		}
		window.clear();
		draw(atl, &window);
		window.display();
	}
	atl.del();
	return 0;
}
