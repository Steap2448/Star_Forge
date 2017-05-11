#include <SFML/Graphics.hpp>
#include <iostream> 
#include "load-save-functions.cpp"
#define Size Vector2f(500,80)
#define HEIGHT 400
#define LENGTH 1270
#define lim 580
#define CHARSIZE 28
#define Size2 Vector2f(125,30)
#define Size3 Vector2f(60,60)
#define SizeS Vector2f(250,80)
#define BASE Vector2f(440,40)
#define NAME Vector2f(205,36)
#define HEIGHT2 300
#define LENGTH2 1600
#define T_SCALE 1
#define WIDTH 768.0
#define speed 6.0
char PULL[11][30]={"system_files/new.png","system_files/load.png","system_files/settings.png","system_files/exit.png","system_files/sun.jpeg","system_files/earth.jpeg","system_files/mercury.jpg","system_files/venus.jpg","system_files/title.png","system_files/accurate.png","system_files/CS.png"};

class comand
{
	public:
	Texture t;
	Vector2f s;
	int func;
	RectangleShape button;
	comand* next;
	comand ()
	{
		func = 1;
	}
	comand(std::string path,Vector2f size,float k,int x,int y)
	{
		t.loadFromFile(path);
		RectangleShape b(k*size);
		b.setTexture(&(t));
		b.setPosition(x*k,y*k);
		button = b;
		s=size;
	}
	int pressed(Vector2i p,float k)
	{
		Vector2f p1;
		p1 = button.getPosition();
		if((p.x>p1.x)&&(p.y>p1.y)&&(p.x<p1.x+s.x)&&(p.y<p1.y+s.y)) return 1;
		else return 0;
	}	
	
};

class object
{
	public:
	Text name;
	RectangleShape Box;
	object* next;
	Atlas_node eq;
	int vs;
	object(Atlas_node a,Font* font,float k)
	{
		eq = a;
		Text t;
		t.setString(a->body.body_name);
		t.setFont(*font);
		t.setColor(Color::White);
		t.setCharacterSize(CHARSIZE*k);
		name = t;
		RectangleShape tmp(SizeS*k);
		tmp.setFillColor(Color::Black);
		tmp.setOutlineThickness(3);
		Box = tmp;
		vs = 1;
	}
	void draw(RenderWindow* window)
	{
		if(vs)
		{
			window->draw(Box);
			window->draw(name);
		}
	}
};

class object_list
{
	public:
	object* first;
	object* last;
	object* current;
	float k;
	int counter;
	int vis;
	int sign;
	Font font;
	Atlas_node active;
	Atlas_node active2;
	object_list(float k1,Font font1)
	{
		font = font1;
		first = NULL;
		last = NULL;
		current = NULL;
		active = NULL;
		active2 = NULL;
		k=k1;
		counter = 0;
		vis = 0;
		sign = 0;
	}
	void add(object* a)
	{
		Vector2f p;
		if(first == NULL)
		{
			first = a;
			last = a;
			current = a;
			a->Box.setPosition((LENGTH-180)*k,(HEIGHT-300)*k);
			a->name.setPosition((LENGTH-130)*k,(HEIGHT-300+20)*k);
		}
		else 
		{
			p = last->Box.getPosition();
			last->next = a;
			last = a;
			
		}
		a->next=NULL;
		a->Box.setPosition((LENGTH-180)*k,p.y+100*k);
		a->name.setPosition((LENGTH-130)*k,p.y+120*k);
		counter++;
	}
	void destroy()
	{
		current=first;
		while(current!=NULL)
		{
			current = first->next;
			delete first;
			first = current;
		}
	}
	void list(Atlas* atl)
	{
		Atlas_node current;
		current = atl->first;
		while(current)	
		{
			object* tmp = new object(current,&font,k);
			add(tmp);
			current = current->next;
		}
	}
	void check(Vector2i p,Atlas* atl)
	{
		if(p.x < (LENGTH2-240)*k||p.x > (LENGTH2+240)*k )
		{
			object* current = first;
			Vector2f p1;
			active = NULL;
			atl->active = NULL;
			while (current!=NULL)
			{
				p1 = current->Box.getPosition();
				if((p.x>p1.x)&&(p.y>p1.y)&&(p.x<p1.x+SizeS.x*k)&&(p.y<p1.y+SizeS.y*k))
				{
					active = current->eq;
					atl->active = current->eq;
					current->Box.setFillColor(Color::Green);
				}
				else current->Box.setFillColor(Color::Black);
				current=current->next;
			}
			return ;
		}
	}
	void check2(Vector2i p,Atlas* atl)
	{
		if(p.x < (LENGTH2-240)*k||p.x > (LENGTH2+240)*k )
		{
			object* current = first;
			Vector2f p1;
			active2 = NULL;
			atl->active2 = NULL;
			while (current!=NULL)
			{
				p1 = current->Box.getPosition();
				if((p.x>p1.x)&&(p.y>p1.y)&&(p.x<p1.x+SizeS.x*k)&&(p.y<p1.y+SizeS.y*k))
				{
					active2 = current->eq;
					atl->active2 = current->eq;
					current->Box.setOutlineColor(Color::Blue);
				}
				else current->Box.setOutlineColor(Color::White);
				current=current->next;
			}
			return ;
		}
	}
	/*void set()
	{
		current = first;
		counter = 0;
		while (current!=NULL)
		{
			current->Box.setPosition((LENGTH-180)*k,(HEIGHT-300+120*counter)*k);
			current->name.setPosition((LENGTH-130)*k,(HEIGHT-300+20+120*counter)*k);
			current = current->next;
			counter++;
		}
		return;
	}*/
	void set(object* obj)
	{
		while (obj!=NULL)
		{
			obj->Box.move(0,-100*k);
			obj->name.move(0,-100*k);
			obj = obj->next;
		}
		return;
	}
	void remove()
	{
		object* tmp;
		object* ntr;
		tmp = first;
		if (tmp->eq == active)
		{
			if(tmp->next)set(tmp->next);
			tmp = first->next;
			delete first;
			first = tmp;
			if(counter == 1) first = NULL;
			active = NULL;
			counter--;
			return;
		}
		while (tmp->next && tmp->next->eq!=active)
		{
			tmp = tmp -> next;
		}
		if(tmp->next==last) last = tmp;
		if(tmp->next)
		{
			set(tmp->next);
			ntr=tmp->next;
		}
		else ntr->next = NULL;
		if (ntr->next) tmp->next=tmp->next->next;
		else tmp->next = NULL;
		delete ntr;
		counter--;
		active = NULL;
		sign = 0;
	}
	void scroll(int j)
	{
		object* current = first;
		Vector2f p1;
		if(sign*j<=0||vis>0)
		{
			vis = 0;
			while(current!=NULL)
			{
				current->name.move(0,j*30*k);
				current->Box.move(0,j*30*k);
				p1=current->Box.getPosition();
				if(p1.y<40*k||p1.y>1000*k) current->vs = 0;
				else current->vs = 1;
				vis+=current->vs;
				current = current->next;
			}
		}
		sign = j;
	}
};

void draw(object_list* ol,RenderWindow* window)
{
	object* current = ol->first;
	while (current!=NULL)
	{
		current->draw(window);
		current=current->next;
	}
	return;
}

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
		a->func = counter;
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
			if((p.x>p1.x)&&(p.y>p1.y)&&(p.x<p1.x+Size.x*k)&&(p.y<p1.y+Size.y*k))
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
			if(limit*k<p1.x) current->button.move(-speed*k,0);
			if((limit-80)*k<p2.x) border.move(-speed/count*k,0);
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
		comand (*tmp)=new comand();
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
		cl->addl(tmp,9);
	}
	return;
}

void Settings_(comand_list* cl)
{
	float k = cl->k;
	comand (*tmp)=new comand;
	cl->addl(tmp,10);
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
	shape->setOrigin(-1,-1);
	shape->setOutlineThickness(1);
	shape->setOutlineColor(Color::Black);
	return shape;
}

class texture
{
	public:
	filename name;
	Texture t;
	int vs;
	RectangleShape sample;
	texture* next;
	texture (float k, filename name1)
	{
		name = name1;
		t.loadFromFile("system_files/object_textures/"+name1.name);
		RectangleShape tmp(Size3*k);
		tmp.setTexture(&t);
		sample = tmp;
	}
	void draw(RenderWindow* window)
	{
		if (vs) window->draw(sample);
	}
	int pressed(Vector2i p,float k)
	{
		Vector2f p1;
		p1 = sample.getPosition();
		if((p.x>p1.x)&&(p.y>p1.y)&&(p.x<p1.x+Size3.x*k)&&(p.y<p1.y+Size3.y*k)) return 1;
		else return 0;
	}
};

class texture_list
{
	public:
	texture* first;
	texture* last;
	texture* current;
	float k;
	int counter;
	int vis;
	int sign;
	std::string path;
	texture_list(float k1)
	{
		first = NULL;
		last = NULL;
		k=k1;
		counter = 0;
		path="_";
		vis = 0;
		sign = 0;
	}
	void add(texture* a)
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
		a->sample.setPosition((1400+counter*(Size3.x+10))*k,(650)*k);
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
	void load(filename_list fnl)
	{
		filename* current;
		current = fnl.first;
		while(current)
		{
			texture* tmp = new texture(k,*current);
			add(tmp);
			current = current->next;
		}
	}
	void scroll(int j)
	{
		texture* current = first;
		if(sign*j<=0||vis>=5)
		{
			vis = 0;
			while(current!=NULL)
			{
				current->sample.move(j*30*k,0);
				Vector2f p=current->sample.getPosition();
				if(p.x<(LENGTH2-230)*k||p.x>(LENGTH2+160)*k) current->vs = 0;
				else current->vs = 1;
				vis+=current->vs;
				current = current->next;
			}
		}
		sign = j;
	}
	void check(Vector2i p)
	{
		texture* current = first;
		Vector2f p1;
		while (current!=NULL)
		{
			p1 = current->sample.getPosition();
			if((p.x>p1.x)&&(p.y>p1.y)&&(p.x<p1.x+Size3.x*k)&&(p.y<p1.y+Size3.y*k))
			{
				path = "system_files/object_textures/"+current->name.name;
			}
			current=current->next;
		}
		return ;
	}
};

void draw(texture_list* cl,RenderWindow* window)
{
	texture* current = cl->first;
	while (current!=NULL)
	{
		current->draw(window);
		current=current->next;
	}
	return;
}

class save_file
{
	public:
	RectangleShape button;
	save_file* next;
	std::string name;
	int vs;
	Text text;
	save_file()
	{
		text.setString("_");
	}
	save_file(float k,std::string name1,Font* font)
	{
		name = name1;
		Text t;
		t.setString(name1.substr(0, name1.find(".")));
		t.setFont(*font);
		t.setColor(Color::White);
		t.setCharacterSize(CHARSIZE*k);
		text = t;
		RectangleShape tmp(Vector2f(Size.x*k*0.9,Size.y*k*0.9));
		tmp.setFillColor(Color::Black);
		tmp.setOutlineThickness(3);
		button = tmp;
		vs = 0;
	}
	void draw(RenderWindow* window)
	{
		if(vs)
		{
			window->draw(button);
			window->draw(text);
		}
	}
};

class save_list
{
	public:
	save_file* first;
	save_file* last;
	save_file* current;
	RectangleShape border;
	float k;
	int counter;
	int vis;
	int sign;
	Font font;
	std::string load;
	save_list(float k1,Font font1)
	{
		font = font1;
		first = NULL;
		last = NULL;
		current = NULL;
		k=k1;
		RectangleShape R(Vector2f(730*k,1100*k));
		R.setOutlineThickness(3);
		R.setFillColor(Color::Black);
		R.setPosition((LENGTH-110)*k,(-10*k));
		border = R;
		counter = 0;
		load = "_";
		vis = 0;
		sign = 0;
	}
	void add(save_file* a)
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
		a->button.setPosition((LENGTH+150*counter)*k,(HEIGHT-300+120*counter)*k);
		a->text.setPosition((LENGTH+50+150*counter)*k,(HEIGHT-300+10+120*counter)*k);
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
	void scroll(int j)
	{
		save_file* current = first;
		Vector2f p1;
		if(sign*j<=0||vis>=8)
		{
			vis = 0;
			while(current!=NULL)
			{
				current->text.move(0,j*30*k);
				current->button.move(0,j*30*k);
				p1=current->button.getPosition();
				if(p1.y<40*k||p1.y>1040*k) current->vs = 0;
				else current->vs = 1;
				vis+=current->vs;
				current = current->next;
			}
		}
		sign = j;
	}
	void check(Vector2i p)
	{
		save_file* current = first;
		Vector2f p1;
		while (current!=NULL)
		{
			p1 = current->button.getPosition();
			if((p.x>p1.x)&&(p.y>p1.y)&&(p.x<p1.x+Size.x*k)&&(p.y<p1.y+Size.y*k))
			{
				load = "Saves/"+current->name;
			}
			current=current->next;
		}
		return ;
	}
	void loading(filename_list fnl)
	{
		filename* current;
		current = fnl.first;
		save_file* tmp;
		while(current)
		{
			tmp = new save_file(k,current->name,&font);
			add(tmp);
			current = current->next;
		}
	}
	void slide(int limit,int count)
	{
		
		save_file* current = first;
		Vector2f p1,p2;
		while (current!=NULL)
		{
			p2 = border.getPosition();
			p1 = current->button.getPosition();
			if(limit*k<p1.x)
			{
				current->button.move(-speed*k,0);
				current->text.move(-speed*k,0);
			}
			if((limit-80)*k<p2.x) border.move(-speed/count*k,0);
			current=current->next;
		}
		return;
	}
	void reset()
	{
		save_file* current = first;
		Vector2f p1;
		counter = 0;
		while (current!=NULL)
		{
			current->button.setPosition((LENGTH+150*counter)*k,(HEIGHT-300+120*counter)*k);
			current->text.setPosition((LENGTH+50+150*counter)*k,(HEIGHT-300+10+120*counter)*k);
			current=current->next;
			counter++;
		}
		border.setPosition((LENGTH-110)*k,(-10*k));
		return;
	}
};

void draw(save_list* cl,RenderWindow* window)
{
	window->draw(cl->border);
	save_file* current = cl->first;
	while (current!=NULL)
	{
		current->draw(window);
		current=current->next;
	}
	return;
}
