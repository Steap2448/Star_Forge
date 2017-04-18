#include <iostream>
#include "celestial_body.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#define CHARSIZE 28
#define Size2 Vector2f(125,30)
#define BASE Vector2f(440,40)
#define HEIGHT2 540
#define LENGTH2 1600
#define T_SCALE 1
using namespace sf;
std::string l = ".";
Color a(200,200,200,255);
float kz = 1;
char PULL2[6][20] = {"   Enter mass:"," Enter radius:","      Enter x:","      Enter y:","     Enter Vx:","     Enter Vy:"};
//char PULL2[6][20] = {"      Enter x:","      Enter y:","     Enter Vx:","     Enter Vy:","     Enter Vx:","     Enter Vy:"};
std::string::size_type sz;

class msBox
{
	public:
	msBox* next;
	RectangleShape base;
	RectangleShape f1;
	RectangleShape f2;
	std::string name;
	std::string x10;
	std::string string1;
	std::string string2;
	Text name_t;
	Text x10_t;
	Text text1;
	Text text2;
	int flag1;
	int flag2;
	int step;
	double res1;
	double res2;
	double all_res;
	msBox (float k,int i,Font* font)
	{
		RectangleShape R(BASE*k);
		RectangleShape fi1(Size2*k);
		RectangleShape fi2(Size2*k);
		fi2.setScale(0.5,0.5);
		R.setOutlineThickness(2);
		R.setFillColor(Color::Black);
		R.setPosition(( LENGTH2-BASE.x/2)*k,(HEIGHT2-BASE.y/2+i*60)*k);
		fi1.setPosition(( LENGTH2-BASE.x/2+180)*k,( HEIGHT2-BASE.y/2+(BASE.y-Size2.y)/2+i*60)*k);
		fi2.setPosition(( LENGTH2-BASE.x/2+360)*k,( HEIGHT2-BASE.y/2+(BASE.y-Size2.y)/4+i*60)*k);
		fi1.setFillColor(a);
		fi2.setFillColor(a);
		base=R;
		f1=fi1;
		f2=fi2;
		name = PULL2[i];
		x10 = "*10";
		name_t.setString(name);
		name_t.setCharacterSize(CHARSIZE*k);
		name_t.setPosition(( LENGTH2-BASE.x/2)*k,(HEIGHT2-BASE.y/2+i*60)*k);
		x10_t.setString(x10);
		x10_t.setCharacterSize(CHARSIZE*k);
		x10_t.setPosition(( LENGTH2-BASE.x/2+310)*k,(HEIGHT2-BASE.y/2+i*60)*k);
		text1.setString(string1);
		text1.setPosition(( LENGTH2-BASE.x/2+185)*k,( HEIGHT2-BASE.y/2+(BASE.y-Size2.y)/2-3+i*60)*k);
		text1.setColor(Color::Black);
		text1.setCharacterSize(CHARSIZE*k);	
		text2.setString(string2);
		text2.setPosition((LENGTH2-BASE.x/2+360+1)*k,( HEIGHT2-BASE.y/2+(BASE.y-Size2.y)/4-2+i*60)*k);
		text2.setColor(Color::Black);
		text2.setCharacterSize(k*CHARSIZE/2.0);
		text1.setFont ( *font );
		text2.setFont ( *font );
		name_t.setFont( *font );
		x10_t.setFont ( *font );
		flag1 = 0;
		flag2 = 0;
		step = 2;
		res1 = 0;
		res2 = 0;
		all_res = 0;
	}
	void update()
	{
		text1.setString(string1);
		text2.setString(string2);
		if(string1.size()) res1=std::stof(string1,&sz);
		else res1=0;
		if(string2.size()) res2=std::stof(string2,&sz);
		else res2=0;
		all_res = res1*pow(10,res2);
	}
	void draw(RenderWindow* window)
	{
		window->draw(base);
		window->draw(f1);
		window->draw(f2);
		window->draw(text1);
		window->draw(name_t);
		window->draw(x10_t);
		window->draw(text2);
		return;
	}
	void step_check(Vector2i p,float k)
	{
		Vector2f p1;
		p1 = f1.getPosition();
		if((p.x>p1.x)&&(p.y>p1.y)&&(p.x<p1.x+Size2.x*k)&&(p.y<p1.y+Size2.y*k))
		{
			step = 0;
			f1.setFillColor(Color::White);
			f2.setFillColor(a);
		}
		else
		{	
			p1 = f2.getPosition();
			if((p.x>p1.x)&&(p.y>p1.y)&&(p.x<p1.x+Size2.x/2*k)&&(p.y<p1.y+Size2.y/2*k))
			{
				step = 1;
				f2.setFillColor(Color::White);
				f1.setFillColor(a);
			}
			else
			{
				step = 2;
				f1.setFillColor(a);
				f2.setFillColor(a);
			}
		}
	}
};

class data
{
	public:
	msBox* first;
	msBox* last;
	msBox* current;
	int counter;
	float k;
	Font font;
	data(float k1,Font font1)
	{
		first = NULL;
		last = NULL;
		k=k1;
		font = font1;
		counter = 0;
	}
	void add(msBox* a)
	{
		if(first == NULL)
		{
			a->next=NULL;
			first = a;
			last = a;
			current = a;
		}
		else 
		{
			a->next=NULL;
			last->next = a;
			last = a;
		}
		counter++;
	}
	void origin()
	{
		while (counter < 6)
		{
			msBox (*tmp)=new msBox(k,counter,&font);
			add(tmp);
		}
	}
	void draw(RenderWindow* window)
	{
		msBox* current = first;
		while (current!=NULL)
		{
			current->draw(window);
			current=current->next;
		}
	}
	void step_check (Vector2i p,float k)
	{
		msBox* current = first;
		while (current!=NULL)
		{
			current->step_check(p,k);
			current=current->next;
		}
	}
	void update()
	{
		msBox* current = first;
		while (current!=NULL)
		{
			current->update();
			current=current->next;
		}
	}
	void destroy()
	{
		while(current!=NULL)
		{
			current = first->next;
			delete first;
			first = current;
		}
	}
};

void input(msBox* a,Event event)
{
	if(a->step==0)
	{
		if(a->string1.size()<7)
		{
			if(event.type == Event::KeyPressed && ((event.key.code == Keyboard::Num0)||event.key.code == Keyboard::Numpad0)) a->string1+="0";
			if(event.type == Event::KeyPressed && ((event.key.code == Keyboard::Num1)||event.key.code == Keyboard::Numpad1)) a->string1+="1";
			if(event.type == Event::KeyPressed && ((event.key.code == Keyboard::Num2)||event.key.code == Keyboard::Numpad2)) a->string1+="2";
			if(event.type == Event::KeyPressed && ((event.key.code == Keyboard::Num3)||event.key.code == Keyboard::Numpad3)) a->string1+="3";
			if(event.type == Event::KeyPressed && ((event.key.code == Keyboard::Num4)||event.key.code == Keyboard::Numpad4)) a->string1+="4";
			if(event.type == Event::KeyPressed && ((event.key.code == Keyboard::Num5)||event.key.code == Keyboard::Numpad5)) a->string1+="5";
			if(event.type == Event::KeyPressed && ((event.key.code == Keyboard::Num6)||event.key.code == Keyboard::Numpad6)) a->string1+="6";
			if(event.type == Event::KeyPressed && ((event.key.code == Keyboard::Num7)||event.key.code == Keyboard::Numpad7)) a->string1+="7";
			if(event.type == Event::KeyPressed && ((event.key.code == Keyboard::Num8)||event.key.code == Keyboard::Numpad8)) a->string1+="8";
			if(event.type == Event::KeyPressed && ((event.key.code == Keyboard::Num9)||event.key.code == Keyboard::Numpad9)) a->string1+="9";
			if(event.type == Event::KeyPressed && (event.key.code == Keyboard::Period )&&(a->flag1==0)) 
			{
				a->string1+=".";
				a->flag1=1;
			}
		}
		if(event.type == Event::KeyPressed && (event.key.code == Keyboard::BackSpace)&&(a->string1.size())) 
		{
			if((a->string1[(a->string1.size())-1]==l)) a->flag1=0;
			a->string1.erase(a->string1.size()-1,1);
		}
	}
	if(a->step==1)
	{
		if(a->string2.size()<7)
		{
			if(event.type == Event::KeyPressed && ((event.key.code == Keyboard::Num0)||event.key.code == Keyboard::Numpad0)) a->string2+="0";
			if(event.type == Event::KeyPressed && ((event.key.code == Keyboard::Num1)||event.key.code == Keyboard::Numpad1)) a->string2+="1";
			if(event.type == Event::KeyPressed && ((event.key.code == Keyboard::Num2)||event.key.code == Keyboard::Numpad2)) a->string2+="2";
			if(event.type == Event::KeyPressed && ((event.key.code == Keyboard::Num3)||event.key.code == Keyboard::Numpad3)) a->string2+="3";
			if(event.type == Event::KeyPressed && ((event.key.code == Keyboard::Num4)||event.key.code == Keyboard::Numpad4)) a->string2+="4";
			if(event.type == Event::KeyPressed && ((event.key.code == Keyboard::Num5)||event.key.code == Keyboard::Numpad5)) a->string2+="5";
			if(event.type == Event::KeyPressed && ((event.key.code == Keyboard::Num6)||event.key.code == Keyboard::Numpad6)) a->string2+="6";
			if(event.type == Event::KeyPressed && ((event.key.code == Keyboard::Num7)||event.key.code == Keyboard::Numpad7)) a->string2+="7";
			if(event.type == Event::KeyPressed && ((event.key.code == Keyboard::Num8)||event.key.code == Keyboard::Numpad8)) a->string2+="8";
			if(event.type == Event::KeyPressed && ((event.key.code == Keyboard::Num9)||event.key.code == Keyboard::Numpad9)) a->string2+="9";
		}
		if(event.type == Event::KeyPressed && (event.key.code == Keyboard::BackSpace)&&(a->string2.size())) 
		{
			if((a->string2[(a->string2.size())-1]==l)) a->flag2=0;
			a->string2.erase(a->string2.size()-1,1);
		}
	}
	
}

void input(data* a,Event event)
{
	msBox* current = a->first;
	while (current!=NULL)
	{
		input(current,event);
		current=current->next;
	}
}

int work(RenderWindow* window,ConvexShape* shape)
{
	Atlas atl;
	Celestial_Body* planet;
	Clock clock;
	int i = 1;
	int fl = 1;
	Text text2;
	Font font;
	font.loadFromFile("arial.ttf");
	data block (kz,font);
	Vector2i p; 
	block.origin();
	while (i) 
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		pthread_mutex_init(&m, NULL);
		time = T_SCALE * time;	
		p=Mouse::getPosition();
		shape->setPosition(p.x,p.y);
		if(fl) Motion(&atl, time, time, 1080);
		Event event;
		while (window->pollEvent(event))
		{	
			p=Mouse::getPosition();
			if((event.type == Event::MouseButtonPressed)&&(event.mouseButton.button == Mouse::Left)) block.step_check(p,kz);
			if(event.type == Event::Closed || 
			(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
			i=0;
			if(event.type == Event::KeyPressed && event.key.code == Keyboard::Return)
			{
				planet = new Celestial_Body((float)(block.first->next->next->all_res),(float)(block.first->next->next->next->all_res),(float)(block.first->next->next->next->next->all_res),(float)(block.first->next->next->next->next->next->all_res),(float)(block.first->next->next->all_res)*0,(float)(block.first->next->next->next->all_res)*0,(float)(block.first->next->all_res),(float)(block.first->all_res));
				atl.add(planet);
				atl.last->avatar.setPosition(atl.last->body.x,atl.last->body.y);
			}
			if(event.type == Event::KeyPressed && event.key.code == Keyboard::P) fl = 1;
			if(event.type == Event::KeyPressed && event.key.code == Keyboard::S) fl = 0;
			input(&block,event);
			block.update();
		}
		window->clear();
		block.draw(window);
		draw(&atl, window);
		window->draw((*shape));
		window->display();
	}
	block.destroy();
	atl.del();
	pthread_mutex_destroy(&m);
	return 0;
}
