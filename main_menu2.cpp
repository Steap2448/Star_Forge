#include "celestial_body.h"
#include <SFML/Graphics.hpp>
#include <iostream> 
#include "method.cpp"
#include "celestial_body.cpp"
#include "interface2.cpp"
#define WIDTH 1080
#define T_SCALE 1

using namespace sf;

int main()
{
	float k=WIDTH/1080.0;
	comand_list cl(k);
	for(;cl.counter<4;)
	{
		comand (*tmp)=new comand;
		cl.add(tmp);
	}
	Celestial_Body Sun(0,0,0,0,0,0,20*k,1.9885e30), Earth(152.1e9,0,0,29.783e3,0,0,7*k,5.9726e24),Mercury(46e9, 0, 0, 58.98e3, 0, 0, 7*k, 0.33011e24), Venus(107.48e9, 0, 0, 35.26e3, 0, 0, 7*k, 4.8675e24);
	RectangleShape title(Vector2f(700*k,200*k));
	Texture t5,t6,t7,t8,t9;
	t5.loadFromFile(PULL[4]);
	t6.loadFromFile(PULL[5]);
	t7.loadFromFile(PULL[6]);
	t8.loadFromFile(PULL[7]);
	t9.loadFromFile(PULL[8]);
	title.setTexture(&t9);
	Atlas atl;
	Clock clock;
	RenderWindow window(VideoMode(1920*k,WIDTH),"Star Forge");
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
	title.setPosition((LENGTH-100)*k,10*k);
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
			//if (button_pressed(p,exit)) window.close();
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
		draw(&cl, &window);
		window.draw((*shape));
		window.display();
	}
	atl.del();
	cl.destroy();
	delete shape;
	return 0;
}

