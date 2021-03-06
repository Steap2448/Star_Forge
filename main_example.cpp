/*This is main for testing. You need this lines for actual program:
 * 	(For Dormand-Prince method) 
    
    //initialization
  	Phase_space k(atl.amount);
	Phase_space* attr = new Phase_space[11];
	for(int i = 0; i <= 10; i++) 
	{
		attr[i].amount = atl.amount;
		attr[i].object = new Phase_vector[attr[i].amount];
		attr[i].mass = new double[attr[i].amount];
	}
	k.load(&atl);
	//iteration
	Motion(&k, &atl, time, STEP, WIDTH, MISTAKE, attr);
	//concluding
	delete[] attr;
	
	
	* Use it as well as Atlas functions. STEP, WIDTH and MISTAKE must be defined! 
	* MISTAKE is a max possible mistake, STEP is the biggest integration step.
 * */

#define WIDTH 600
#define T_SCALE 1

#include "general.hpp"

int main()
{
	Clock clock; 
	RenderWindow window(VideoMode(WIDTH,WIDTH),"test");
	Atlas atl;
	Celestial_Body Sun(0,0,0,0,0,0,5,1.9885e30), Earth(152.1e9,0,0,29.783e3,0,0,0.5,5.9726e24), Moon(x_satellite(0.4055e9, &Earth), y_satellite(0, &Earth), v_x_satellite(0, &Earth), v_y_satellite(964, &Earth), 0, 0, 0.5, 73.46e21), Mars(206.62e9 , 0, 0, 26.50e3, 0, 0, 3, 0.64171e24);
	Celestial_Body Mercury(46e9, 0, 0, 58.98e3, 0, 0, 3, 0.33011e24), Venus(107.48e9, 0, 0, 35.26e3, 0, 0, 3, 4.8675e24);//, Jupiter(740.52e9, 0, 0, 13.72e3, 0, 0, 3, 1898.19e24);
	atl.add(&Sun);
	atl.add(&Earth);
	atl.add(&Mars);	
	atl.add(&Mercury);
	atl.add(&Venus);
	Phase_space* attr = attr_creator(&atl);
	atl.add(&Moon);
	attr_add(attr, &Moon);
	int l = 2;
	while (window.isOpen()&&(l != 0)) 
	{
		float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
		clock.restart(); //перезагружает время
		time = T_SCALE * time;
		//l--;
		//argument.scale = WIDTH;
		//argument.step = time;
		//argument.t_scale = time;
		//Motion_paral_mod(&argument);
		//Motion_paral(&atl, &pth, time, time);
		//Motion(&atl, time, time, WIDTH);
		//k.out();
		//k.out();
		Motion(&atl, time, 0.01 * time, WIDTH, attr);
		//k.out();
    	//pth.launch(time, time, WIDTH);
		//atl.move(WIDTH);
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
	delete[] attr;
	return 0;
}
