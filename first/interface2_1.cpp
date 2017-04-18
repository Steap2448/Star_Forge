#include <SFML/Graphics.hpp>
#include <iostream> 
#define Size Vector2f(500,80)
#define HEIGHT 400
#define LENGTH 1270
#define lim 580
char PULL[9][30]={"system files/new.png","system files/load.png","system files/settings.png","system files/exit.png","system files/sun.png","system files/earth.png","system files/mercury.png","system files/venus.png","system files/title.png"};

struct comand
{
	
	Texture t;
	int func;
	RectangleShape button;
	comand* next;
};

class comand_list
{
	public:
	comand* first;
	comand* last;
	comand* current;
	RectangleShape border;
	float k;
	int counter;
	int mode;
	comand_list(float k1)
	{
		first = NULL;
		last = NULL;
		k=k1;
		RectangleShape R(Vector2f(730*k,1100*k));
		R.setOutlineThickness(3);
		R.setFillColor(Color::Black);
		R.setPosition((LENGTH-110)*k,(-10*k));
		border = R;
		counter = 0;
		mode=-1;
	}
	void add(comand* a)
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
		a->t.loadFromFile(PULL[counter]);
		RectangleShape b(k*Size);
		b.setTexture(&(a->t));
		b.setPosition(LENGTH*k,(HEIGHT+100*counter)*k);
		a->button = b;
		a->func = counter;
		counter++;
	}
	void addl(comand* a,int s)
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
		a->t.loadFromFile(PULL[counter+s]);
		RectangleShape b(k*Size);
		b.setTexture(&(a->t));
		b.setPosition((LENGTH+150*counter)*k,(HEIGHT+100*counter)*k);
		a->button = b;
		a->func = counter+s;
		counter++;
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
	void check(Vector2i p)
	{
		comand* current = first;
		Vector2f p1;
		while (current!=NULL)
		{
			p1 = current->button.getPosition();
			if((p.x>p1.x)&&(p.y>p1.y)&&(p.x<p1.x+Size.x)&&(p.y<p1.y+Size.y))
			{
				mode = current->func;
			}
			current=current->next;
		}
		return ;
	}
	void slide(int limit,int count)
	{
		comand* current = first;
		Vector2f p1,p2;
		while (current!=NULL)
		{
			p2 = border.getPosition();
			p1 = current->button.getPosition();
			if(limit*k<p1.x) current->button.move(-4*k*k,0);
			if((limit-80)*k<p2.x) border.move(-4.0/count*k*k,0);
			current=current->next;
		}
		return;
	}
	void reset()
	{
		comand* current = first;
		Vector2f p1;
		counter = 0;
		while (current!=NULL)
		{
			current->button.setPosition((LENGTH+150*counter)*k,(HEIGHT+100*counter)*k);
			current=current->next;
			counter++;
		}
		border.setPosition((LENGTH-110)*k,(-10*k));
		return;
	}
};
	
void draw(comand_list* cl,RenderWindow* window)
{
	window->draw(cl->border);
	comand* current = cl->first;
	while (current!=NULL)
	{
		window->draw(current->button);
		current=current->next;
	}
	return;
}

void main_menu(comand_list* cl,Atlas* atl,Texture* t)
{
	float k = cl->k;
	for(;cl->counter<4;)
	{
		comand (*tmp)=new comand;
		cl->add(tmp);
	}
	Celestial_Body Sun(0,0,0,0,0,0,20*k,1.9885e30), Earth(152.1e9,0,0,29.783e3,0,0,7*k,5.9726e24),Mercury(46e9, 0, 0, 58.98e3, 0, 0, 7*k, 0.33011e24), Venus(107.48e9, 0, 0, 35.26e3, 0, 0, 7*k, 4.8675e24);
	RectangleShape title(Vector2f(700*k,200*k)),line(Vector2f(3*k,1080*k));
	Texture t5,t6,t7,t8;
	t[0].loadFromFile(PULL[4]);
	t[1].loadFromFile(PULL[5]);
	t[2].loadFromFile(PULL[6]);
	t[3].loadFromFile(PULL[7]);
	atl->add(&Sun);
	atl->add(&Earth);
	atl->add(&Mercury);
	atl->add(&Venus);
	atl->first->avatar.setTexture(&t[0]);
	atl->first->next->avatar.setTexture(&t[1]);
	atl->first->next->next->avatar.setTexture(&t[2]);
	atl->first->next->next->next->avatar.setTexture(&t[3]);
	return;
}

void New_(comand_list* cl)
{
	float k = cl->k;
	for(;cl->counter<2;)
	{
		comand (*tmp)=new comand;
		cl->addl(tmp,0);
	}
	return;
}

ConvexShape* mouse_create()
{
	ConvexShape (*shape) = new ConvexShape;
	shape->setPointCount(4);
	shape->setPoint(0, sf::Vector2f(0, 0));
	shape->setPoint(1, sf::Vector2f(10, 20));
	shape->setPoint(2, sf::Vector2f(10, 10));
	shape->setPoint(3, sf::Vector2f(20, 10));
	shape->setOutlineThickness(1);
	shape->setOutlineColor(Color::Black);
	return shape;
}
