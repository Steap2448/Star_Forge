#include <SFML/Graphics.hpp>
#include <iostream> 
#define Size Vector2f(500,80)
#define HEIGHT 400
#define LENGTH 1270
char PULL[9][30]={"system files/new.png","system files/load.png","system files/settings.png","system files/exit.png","system files/sun.png","system files/earth.png","system files/mercury.png","system files/venus.png","system files/title.png"};

int button_pressed (Vector2i p,RectangleShape button)
{
	Vector2f p1=button.getPosition();
	if((p.x>p1.x)&&(p.y>p1.y)&&(p.x<p1.x+Size.x)&&(p.y<p1.y+Size.y)) return 1;
	else return 0;
}
	
struct comand
{
	Texture t;
	RectangleShape button;
	comand* next;
};

class comand_list
{
	public:
	comand* first;
	comand* last;
	comand* current;
	float k;
	int counter;
	comand_list(float k1)
	{
		first = NULL;
		last = NULL;
		k=k1;
		counter = 0;
	}
	void add(comand* a)
	{
		if(first == NULL)
		{
			a->next=NULL;
			first = a;
			last = a;
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
};
	
void draw(comand_list* cl,RenderWindow* window)
{
	comand* current = cl->first;
	while (current!=NULL)
	{
		window->draw(current->button);
		current=current->next;
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
