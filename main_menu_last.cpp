#include "general.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "input_last.cpp"
#define T_SCALE 1
float k=WIDTH/1080.0;

using namespace sf;

int main()
{
	Font font;
	font.loadFromFile("arial.ttf");
	filename_list list_ptr;
	dir_preview(&list_ptr,"Saves");
	save_list sl(k,font);
	sl.loading(list_ptr);
	int j=-1;
	comand_list cl(k),New(k),Settings(k);
	Music furi;
	furi.openFromFile("furi.ogg");
	furi.play();
	Texture t[4];
	Texture t9;
	t9.loadFromFile(PULL[8]);
	RectangleShape title(Vector2f(700*k,200*k)),background(Vector2f(1000*k,1080*k));
	title.setTexture(&t9);
	Atlas atl;
	Clock clock;
	RenderWindow window(VideoMode(1920*k,WIDTH),"Star Forge"/*,Style::Fullscreen*/);
	window.setMouseCursorVisible(false);
	ConvexShape* shape = mouse_create();
	Vector2i p;
	main_menu(&cl,&atl,t);
	New_(&New);
	Settings_(&Settings);
	background.setFillColor(Color::Black);
	background.setPosition(k*LENGTH,0);
	title.setPosition((LENGTH-100)*k,10*k);
	window.setKeyRepeatEnabled (false);
	furi.setLoop(true);
	Phase_space* attr = attr_creator(&atl); // Проверка пустого атласа и атласа с одним объектом(Alex: done)
	while (window.isOpen()) 
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = T_SCALE * time;	
		//atl.move(WIDTH);
		p=Mouse::getPosition(window);
		shape->setPosition(p.x,p.y);
		Event event;
		while (window.pollEvent(event))
		{
			if(event.type == Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Left&&(cl.mode!=-1)&&(p.x>(LENGTH-110)*k))
				{
					cl.current->button.move(80*k,0);
					cl.mode=-1;
					New.reset();
					sl.reset();
					Settings.reset();
				}
				if (event.mouseButton.button == Mouse::Left&&cl.mode==0)
				{
					New.current=New.first;
					New.check(p);
					if(New.mode==0) 
					{
						Atlas atl;
						work(&window,shape,k,atl);
						clock.restart();
					}
				}		
				if (event.mouseButton.button == Mouse::Left&&cl.mode==1)
				{
					sl.current=sl.first;
					sl.check(p);
					if(sl.load!="_") 
					{
						Atlas atl;
						load_system (sl.load.substr(6),&atl);
						work(&window,shape,k,atl);
						sl.load="_";
						clock.restart();
					}
				}
				if (event.mouseButton.button == Mouse::Left&&cl.mode==-1)
				{
					cl.current=cl.first;
					cl.check(p);
					if(cl.mode==-1) std::cout<<"main\n";
					else 
					{
						if(cl.mode==3) window.close();
						for (int i=1;i<=cl.mode;i++)
						{
							cl.current=cl.current->next;
						}
						cl.current->button.move(-80*k,0);
					}
				}
			}
			if(event.type == Event::Closed || 
			(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)&&(cl.mode==-1))
			window.close();
			if((event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)&&(cl.mode!=-1))
			{
				cl.current->button.move(80*k,0);
				cl.mode=-1;
				New.reset();
				sl.reset();
				Settings.reset();
			}
		}
		window.clear();
		draw(&atl, &window);
		if(cl.mode==0) 
		{
			draw(&New,&window);
			New.slide(lim,New.counter);
		}
		if(cl.mode==1) 
		{
			draw(&sl,&window);
			sl.slide(lim+50,list_ptr.counter);
		}
		if(cl.mode==2) 
		{
			draw(&Settings,&window);
			Settings.slide(lim,Settings.counter);
		}
		Motion(&atl, time, 0.1 * time, WIDTH, 0.01e-19, attr);
		window.draw(background);
		draw(&cl, &window);
		window.draw(title);
		window.draw((*shape));
		window.display();
	}
	atl.del();
	cl.destroy();
	sl.destroy();
	New.destroy();
	list_ptr.destroy();
	Settings.destroy();
	delete[] attr;
	delete shape;
	return 0;
}

