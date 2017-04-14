#define WIDTH 600
#define T_SCALE 1

#include "celestial_body.h"
#include "celestial_body.cpp"
#include <SFML/Graphics.hpp>
#include <iostream> 
#include "method.cpp"
#include "pthread_mod.h"
#include "pthread_mod.cpp"

using namespace sf;
int main()
{
	Clock clock; 
	RenderWindow window(VideoMode(WIDTH,WIDTH),"test");
	Atlas atl;
	Celestial_Body Sun(0,0,0,0,0,0,5,1.9885e30), Earth(152.1e9,0,0,29.783e3,0,0,1,5.9726e24), Mars(206.62e9 , 0, 0, 26.50e3, 0, 0, 1, 0.64171e24);
	Celestial_Body Mercury(46e9, 0, 0, 58.98e3, 0, 0, 1, 0.33011e24), Venus(107.48e9, 0, 0, 35.26e3, 0, 0, 1, 4.8675e24);//, Jupiter(740.52e9, 0, 0, 13.72e3, 0, 0, 3, 1898.19e24);
	atl.add(&Sun);
	atl.add(&Earth);
	atl.add(&Mars);	
	atl.add(&Mercury);
	atl.add(&Venus);
	//arg_mod argument;
	//argument.atlas = &atl;
	//argument.start = atl.first;
	//argument.finish = atl.last;
	Pthread_base pth = Pthread_base(5, &atl);
	while (window.isOpen()) 
	{
		float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
		clock.restart(); //перезагружает время
		pthread_mutex_init(&m, NULL);
		time = T_SCALE * time;
		//argument.scale = WIDTH;
		//argument.step = time;
		//argument.t_scale = time;
		//Motion_paral_mod(&argument);
		//Motion_paral(&atl, &pth, time, time);
		//Motion(&atl, time, time, WIDTH);
		pth.launch(5 * time, time, WIDTH);
		atl.move(WIDTH);
		Event event;
		while (window.pollEvent(event))
		{
			if(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			window.close();
		}
		window.clear();
		draw(&atl, &window);
		window.display();
		cout<<"done\n";
	}
	atl.del();
	pth.del();
	pthread_mutex_destroy(&m);
	return 0;
}
