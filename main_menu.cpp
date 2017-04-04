#include "celestial_body.h"
#include <SFML/Graphics.hpp>
#include <iostream> 
#include "method.cpp"
#include "celestial_body.cpp"
#include "interface.cpp"
#define WIDTH 1080
#define T_SCALE 1

using namespace sf;

int main()
{
	Celestial_Body Sun(0,0,0,0,0,0,20,1.9885e30), Earth(152.1e9,0,0,29.783e3,0,0,7,5.9726e24),Mercury(46e9, 0, 0, 58.98e3, 0, 0, 7, 0.33011e24), Venus(107.48e9, 0, 0, 35.26e3, 0, 0, 7, 4.8675e24);
	RectangleShape settings(Size),exit(Size),load(Size),new1(Size),title(Vector2f(700,200));
	Texture t1,t2,t3,t4,t5,t6,t7,t8,t9;
	t1.loadFromFile("system files/settings.png");
	t2.loadFromFile("system files/exit.png");
	t3.loadFromFile("system files/load.png");
	t4.loadFromFile("system files/new.png");
	t5.loadFromFile("system files/sun.png");
	t6.loadFromFile("system files/earth.png");
	t7.loadFromFile("system files/mercury.png");
	t8.loadFromFile("system files/venues.png");
	t9.loadFromFile("system files/title.png");
	settings.setTexture(&t1);
	exit.setTexture(&t2);
	load.setTexture(&t3);
	new1.setTexture(&t4);
	title.setTexture(&t9);
	Atlas atl;
	Clock clock;
	RenderWindow window(VideoMode(1920,1080),"Star Forge");
	window.setMouseCursorVisible(false);
	ConvexShape* shape = mouse_create();
	Vector2i p;
	Vector2f p1;
	atl.add(Sun);
	atl.add(Earth);
	atl.add(Mercury);
	atl.add(Venus);
	atl.first->avatar.setTexture(&t5);
	atl.first->next->avatar.setTexture(&t6);
	atl.first->next->next->avatar.setTexture(&t7);
	atl.first->next->next->next->avatar.setTexture(&t8);
	Phase_vector v1,v2;
	title.setPosition(LENGTH-100,10);
	new1.setPosition(LENGTH,HEIGHT);
	load.setPosition(LENGTH,HEIGHT+100);
	settings.setPosition(LENGTH,HEIGHT+200);
	exit.setPosition(LENGTH,HEIGHT+300);
	while (window.isOpen()) 
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = T_SCALE * time;	
		Motion(atl, time, WIDTH);
		p=Mouse::getPosition();
		shape->setPosition(p.x,p.y);
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (button_pressed(p,exit)) window.close();
		}
		Event event;
		while (window.pollEvent(event))
		{
			if(event.type == Event::Closed || 
			(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
			window.close();
		}
		window.clear();
		draw(atl, &window);
		window.draw(title);
		window.draw(exit);
		window.draw(new1);
		window.draw(settings);
		window.draw(load);
		window.draw((*shape));
		window.display();
	}
	atl.del();
	return 0;
}

