#define WIDTH 600
#define T_SCALE 1

#include "general.hpp"

int main()
{
	Clock clock; 
	RenderWindow window(VideoMode(WIDTH,WIDTH),"test");
	Atlas atl;
	Celestial_Body Sun(0,0,0,0,0,0,5,1.9885e30), Earth(152.1e9,0,0,0,0,0,3,5.9726e24), Moon(x_satellite(0.4055e9, &Earth), y_satellite(0, &Earth), v_x_satellite(0, &Earth), v_y_satellite(1350, &Earth), 0, 0, 1, 73.46e21), Mars(206.62e9 , 0, 0, 26.50e3, 0, 0, 3, 0.64171e24);
	Celestial_Body Mercury(46e9, 0, 0, 58.98e3, 0, 0, 3, 0.33011e24), Venus(107.48e9, 0, 0, 35.26e3, 0, 0, 3, 4.8675e24);//, Jupiter(740.52e9, 0, 0, 13.72e3, 0, 0, 3, 1898.19e24);
	atl.add(&Sun);
	atl.add(&Earth);
	atl.add(&Mars);	
	atl.add(&Mercury);
	atl.add(&Venus);
	atl.add(&Moon);
	//arg_mod argument;
	//argument.atlas = &atl;
	//argument.start = atl.first;
	//argument.finish = atl.last;
	std::cout<<"1\n";
	//Pthread_base pth = Pthread_base(5, &atl);
	std::cout<<"1\n";
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
		Motion(&atl, time, time, WIDTH);
    	//	pth.launch(time, time, WIDTH);
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
	}
	atl.del();
	//pth.del();
	pthread_mutex_destroy(&m);
	return 0;
}
