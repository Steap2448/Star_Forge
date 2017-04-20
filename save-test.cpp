#include "load-save-functions.cpp"
#include "celestial_body.h"
#include "celestial_body.cpp"
#include "interface.cpp"
#include <SFML/Graphics.hpp>
#include <iostream> 
#define WIDTH 600
#define T_SCALE 1
using namespace sf;

int main()
{
	float k=WIDTH/1080.0;
	Celestial_Body Sun(0,0,0,0,0,0,20*k,1.9885e30, "system_files/sun.png", "SUN"), Earth(152.1e9,0,0,29.783e3,0,0,7*k,5.9726e24, "system_files/earth.png", "EARTH"),Mercury(46e9, 0, 0, 58.98e3, 0, 0, 7*k, 0.33011e24, "system_files/mercury.png", "MERCURY"), Venus(107.48e9, 0, 0, 35.26e3, 0, 0, 7*k, 4.8675e24, "system_files/venus.png", "VENUS");
	RectangleShape settings(k*Size),exit(k*Size),load(k*Size),new1(k*Size),title(Vector2f(700*k,200*k));
	Texture t1,t2,t3,t4,t5,t6,t7,t8,t9;
	t1.loadFromFile("system_files/settings.png");
	t2.loadFromFile("system_files/exit.png");
	t3.loadFromFile("system_files/load.png");
	t4.loadFromFile("system_files/new.png");
	t5.loadFromFile("system_files/sun.png");
	t6.loadFromFile("system_files/earth.png");
	t7.loadFromFile("system_files/mercury.png");
	t8.loadFromFile("system_files/venus.png");
	t9.loadFromFile("system_files/title.png");
	settings.setTexture(&t1);
	exit.setTexture(&t2);
	load.setTexture(&t3);
	new1.setTexture(&t4);
	title.setTexture(&t9);
	Atlas atl;
	atl.add(&Sun);
	atl.add(&Earth);
	atl.add(&Mercury);
	atl.add(&Venus);
	atl.first->avatar.setTexture(&t5);
	atl.first->next->avatar.setTexture(&t6);
	atl.first->next->next->avatar.setTexture(&t7);
	atl.first->next->next->next->avatar.setTexture(&t8);
	atl.name = "Correct_save";
	save_system(atl, "Correct_save");
	atl.del();
	return 0;
}
