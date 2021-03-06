#include "interface_last.cpp"
#define CONST 1
#define CONST1 0.01
using namespace sf;
std::string l = ".";
std::string l2 = "-";
Color gray(200,200,200,255);
char NAME_PULL[2][20] = {"  OBJECT NAME:","  SYSTEM NAME:"};
char PULL2[6][20] = {"          Mass:","       Radius:","                X:","                Y:","               Vx:","               Vy:"};
std::string::size_type sz;

class title
{
	public:
	RectangleShape base;
	RectangleShape f;
	std::string name;
	std::string intro;
	Text name_t;
	Text intro_t;
	int flag;
	title (float k,int i,Font* font)
	{
		RectangleShape R(BASE*k);
		R.setOutlineThickness(2);
		R.setFillColor(Color::Black);
		R.setPosition(( LENGTH2-BASE.x/2)*k,(HEIGHT2-BASE.y/2-60*(2*i+1))*k);
		RectangleShape fi(NAME*k);
		fi.setPosition(( LENGTH2-BASE.x/2+230)*k,(HEIGHT2-BASE.y/2-60*(2*i+1)+2)*k);
		fi.setFillColor(gray);
		base=R;
		f=fi;
		intro = NAME_PULL[i];
		intro_t.setString(intro);
		intro_t.setCharacterSize(CHARSIZE*k);
		intro_t.setPosition(( LENGTH2-BASE.x/2)*k,(HEIGHT2-BASE.y/2-60*(2*i+1))*k);
		intro_t.setFont( *font );
		name_t.setFont( *font );
		name_t.setCharacterSize(CHARSIZE*k);
		name_t.setPosition(( LENGTH2-BASE.x/2+232)*k,(HEIGHT2-BASE.y/2-60*(2*i+1)+2)*k);
		name_t.setColor(Color::Black);
		flag = 0;
	}
	void draw(RenderWindow* window)
	{
		window->draw(base);
		window->draw(f);
		window->draw(intro_t);
		window->draw(name_t);
		return;
	}
	void check(Vector2i p,float k)
	{
		Vector2f p1;
		p1 = f.getPosition();
		if((p.x>p1.x)&&(p.y>p1.y)&&(p.x<p1.x+NAME.x*k)&&(p.y<p1.y+NAME.y*k))
		{
			f.setFillColor(Color::White);
			flag = 1;
		}
		else
		{
			f.setFillColor(gray);
			flag = 0;
		}
	}
	void update()
	{
		name_t.setString(name);
	}
		void reset()
	{
		name = "";
	}
};

class msBox
{
	public:
	msBox* next;
	msBox* first;
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
		fi1.setFillColor(gray);
		fi2.setFillColor(gray);
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
	}
	void last_update()
	{
		text1.setString(string1);
		text2.setString(string2);
		if(string1.size() && (string1[(string1.size())-1]!=l2)) res1=std::stof(string1,&sz);
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
			f2.setFillColor(gray);
		}
		else
		{	
			p1 = f2.getPosition();
			if((p.x>p1.x)&&(p.y>p1.y)&&(p.x<p1.x+Size2.x/2*k)&&(p.y<p1.y+Size2.y/2*k))
			{
				step = 1;
				f2.setFillColor(Color::White);
				f1.setFillColor(gray);
			}
			else
			{
				step = 2;
				f1.setFillColor(gray);
				f2.setFillColor(gray);
			}
		}
	}
	void reset()
	{
		string1 = "";
		string2 = "";
		flag1 = 0;
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
			a->first = first;
		}
		else 
		{
			a->next=NULL;
			last->next = a;
			last = a;
			a->first = first;
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
	void last_update()
	{
		msBox* current = first;
		while (current!=NULL)
		{
			current->last_update();
			current=current->next;
		}
	}
	void reset()
	{
		msBox* current = first;
		while (current!=NULL)
		{
			current->reset();
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

void input(title* a,Event event)
{
	if(a->flag==1)
	{
		if(a->name.size()<10)
		{
			if(event.type == Event::KeyPressed && (event.key.code == Keyboard::Q)) a->name+="Q";
			if(event.type == Event::KeyPressed && (event.key.code == Keyboard::W)) a->name+="W";
			if(event.type == Event::KeyPressed && (event.key.code == Keyboard::E)) a->name+="E";
			if(event.type == Event::KeyPressed && (event.key.code == Keyboard::R)) a->name+="R";
			if(event.type == Event::KeyPressed && (event.key.code == Keyboard::T)) a->name+="T";
			if(event.type == Event::KeyPressed && (event.key.code == Keyboard::Y)) a->name+="Y";
			if(event.type == Event::KeyPressed && (event.key.code == Keyboard::U)) a->name+="U";
			if(event.type == Event::KeyPressed && (event.key.code == Keyboard::I)) a->name+="I";
			if(event.type == Event::KeyPressed && (event.key.code == Keyboard::O)) a->name+="O";
			if(event.type == Event::KeyPressed && (event.key.code == Keyboard::P)) a->name+="P";
			if(event.type == Event::KeyPressed && (event.key.code == Keyboard::A)) a->name+="A";
			if(event.type == Event::KeyPressed && (event.key.code == Keyboard::S)) a->name+="S";
			if(event.type == Event::KeyPressed && (event.key.code == Keyboard::D)) a->name+="D";
			if(event.type == Event::KeyPressed && (event.key.code == Keyboard::F)) a->name+="F";
			if(event.type == Event::KeyPressed && (event.key.code == Keyboard::G)) a->name+="G";
			if(event.type == Event::KeyPressed && (event.key.code == Keyboard::H)) a->name+="H";
			if(event.type == Event::KeyPressed && (event.key.code == Keyboard::J)) a->name+="J";
			if(event.type == Event::KeyPressed && (event.key.code == Keyboard::K)) a->name+="K";
			if(event.type == Event::KeyPressed && (event.key.code == Keyboard::L)) a->name+="L";
			if(event.type == Event::KeyPressed && (event.key.code == Keyboard::Z)) a->name+="Z";
			if(event.type == Event::KeyPressed && (event.key.code == Keyboard::X)) a->name+="X";
			if(event.type == Event::KeyPressed && (event.key.code == Keyboard::C)) a->name+="C";
			if(event.type == Event::KeyPressed && (event.key.code == Keyboard::V)) a->name+="V";
			if(event.type == Event::KeyPressed && (event.key.code == Keyboard::B)) a->name+="B";
			if(event.type == Event::KeyPressed && (event.key.code == Keyboard::N)) a->name+="N";
			if(event.type == Event::KeyPressed && (event.key.code == Keyboard::M)) a->name+="M";
			if(event.type == Event::KeyPressed && ((event.key.code == Keyboard::Num0)||event.key.code == Keyboard::Numpad0)) a->name+="0";
			if(event.type == Event::KeyPressed && ((event.key.code == Keyboard::Num1)||event.key.code == Keyboard::Numpad1)) a->name+="1";
			if(event.type == Event::KeyPressed && ((event.key.code == Keyboard::Num2)||event.key.code == Keyboard::Numpad2)) a->name+="2";
			if(event.type == Event::KeyPressed && ((event.key.code == Keyboard::Num3)||event.key.code == Keyboard::Numpad3)) a->name+="3";
			if(event.type == Event::KeyPressed && ((event.key.code == Keyboard::Num4)||event.key.code == Keyboard::Numpad4)) a->name+="4";
			if(event.type == Event::KeyPressed && ((event.key.code == Keyboard::Num5)||event.key.code == Keyboard::Numpad5)) a->name+="5";
			if(event.type == Event::KeyPressed && ((event.key.code == Keyboard::Num6)||event.key.code == Keyboard::Numpad6)) a->name+="6";
			if(event.type == Event::KeyPressed && ((event.key.code == Keyboard::Num7)||event.key.code == Keyboard::Numpad7)) a->name+="7";
			if(event.type == Event::KeyPressed && ((event.key.code == Keyboard::Num8)||event.key.code == Keyboard::Numpad8)) a->name+="8";
			if(event.type == Event::KeyPressed && ((event.key.code == Keyboard::Num9)||event.key.code == Keyboard::Numpad9)) a->name+="9";
		}
			if(event.type == Event::KeyPressed && (event.key.code == Keyboard::BackSpace)&&(a->name.size()))
			a->name.erase(a->name.size()-1,1);
	}
}
			

void input(msBox* a,Event* event)
{
	if(a->step==0)
	{
		if(event->type == Event::KeyPressed && (event->key.code == Keyboard::Tab))
		{
			a->step=1;
			a->f2.setFillColor(Color::White);
			a->f1.setFillColor(gray);
			return;
		}		
		if(a->string1.size()<7)
		{
			if(event->type == Event::KeyPressed && ((event->key.code == Keyboard::Num0)||event->key.code == Keyboard::Numpad0)) a->string1+="0";
			if(event->type == Event::KeyPressed && ((event->key.code == Keyboard::Num1)||event->key.code == Keyboard::Numpad1)) a->string1+="1";
			if(event->type == Event::KeyPressed && ((event->key.code == Keyboard::Num2)||event->key.code == Keyboard::Numpad2)) a->string1+="2";
			if(event->type == Event::KeyPressed && ((event->key.code == Keyboard::Num3)||event->key.code == Keyboard::Numpad3)) a->string1+="3";
			if(event->type == Event::KeyPressed && ((event->key.code == Keyboard::Num4)||event->key.code == Keyboard::Numpad4)) a->string1+="4";
			if(event->type == Event::KeyPressed && ((event->key.code == Keyboard::Num5)||event->key.code == Keyboard::Numpad5)) a->string1+="5";
			if(event->type == Event::KeyPressed && ((event->key.code == Keyboard::Num6)||event->key.code == Keyboard::Numpad6)) a->string1+="6";
			if(event->type == Event::KeyPressed && ((event->key.code == Keyboard::Num7)||event->key.code == Keyboard::Numpad7)) a->string1+="7";
			if(event->type == Event::KeyPressed && ((event->key.code == Keyboard::Num8)||event->key.code == Keyboard::Numpad8)) a->string1+="8";
			if(event->type == Event::KeyPressed && ((event->key.code == Keyboard::Num9)||event->key.code == Keyboard::Numpad9)) a->string1+="9";
			if(event->type == Event::KeyPressed && ((event->key.code == Keyboard::Subtract)||(event->key.code == Keyboard::Dash)) && a->string1.size()==0) a->string1+="-";
			if(event->type == Event::KeyPressed && ((event->key.code == Keyboard::Period )||(event->key.code == Keyboard::Comma))&&(a->flag1==0)) 
			{
				a->string1+=".";
				a->flag1=1;
			}
		}
		if(event->type == Event::KeyPressed && (event->key.code == Keyboard::BackSpace)&&(a->string1.size())) 
		{
			if((a->string1[(a->string1.size())-1]==l)) a->flag1=0;
			a->string1.erase(a->string1.size()-1,1);
		}
	}
	if(a->step==1)
	{
		if(event->type == Event::KeyPressed && (event->key.code == Keyboard::Tab))
		{
			a->step=2;
			a->f2.setFillColor(gray);
			a->f1.setFillColor(gray);
			if(a->next)
			{
				a->next->step = 0;
				a->next->f1.setFillColor(Color::White);
			}
			else
			{
				a->first->step = 0;
				a->first->f1.setFillColor(Color::White);
			}
			event->key.code = Keyboard::PageUp;
			return;
		}		
		if(a->string2.size()<7)
		{
			if(event->type == Event::KeyPressed && ((event->key.code == Keyboard::Num0)||event->key.code == Keyboard::Numpad0)) a->string2+="0";
			if(event->type == Event::KeyPressed && ((event->key.code == Keyboard::Num1)||event->key.code == Keyboard::Numpad1)) a->string2+="1";
			if(event->type == Event::KeyPressed && ((event->key.code == Keyboard::Num2)||event->key.code == Keyboard::Numpad2)) a->string2+="2";
			if(event->type == Event::KeyPressed && ((event->key.code == Keyboard::Num3)||event->key.code == Keyboard::Numpad3)) a->string2+="3";
			if(event->type == Event::KeyPressed && ((event->key.code == Keyboard::Num4)||event->key.code == Keyboard::Numpad4)) a->string2+="4";
			if(event->type == Event::KeyPressed && ((event->key.code == Keyboard::Num5)||event->key.code == Keyboard::Numpad5)) a->string2+="5";
			if(event->type == Event::KeyPressed && ((event->key.code == Keyboard::Num6)||event->key.code == Keyboard::Numpad6)) a->string2+="6";
			if(event->type == Event::KeyPressed && ((event->key.code == Keyboard::Num7)||event->key.code == Keyboard::Numpad7)) a->string2+="7";
			if(event->type == Event::KeyPressed && ((event->key.code == Keyboard::Num8)||event->key.code == Keyboard::Numpad8)) a->string2+="8";
			if(event->type == Event::KeyPressed && ((event->key.code == Keyboard::Num9)||event->key.code == Keyboard::Numpad9)) a->string2+="9";
		}
		if(event->type == Event::KeyPressed && (event->key.code == Keyboard::BackSpace)&&(a->string2.size())) 
		{
			if((a->string2[(a->string2.size())-1]==l)) a->flag2=0;
			a->string2.erase(a->string2.size()-1,1);
		}
	}
	
}

void input(data* a,Event* event)
{
	msBox* current = a->first;
	while (current!=NULL)
	{
		input(current,event);
		current=current->next;
	}
}

int work(RenderWindow* window,ConvexShape* shape,RectangleShape bg,float k,Atlas atl,Music* furi,int mode)
{
	Music me;
	me.openFromFile("system_files/me.ogg");
	me.setLoop(true);
	filename_list list_ptr;
	dir_preview(&list_ptr,"system_files/object_textures");
	Texture r,r1;
	r.loadFromFile("system_files/hint1.png");
	r1.loadFromFile("system_files/error.png");
	Celestial_Body* planet;
	object* obj; 
	comand save("system_files/save.png",SizeS,k,(LENGTH+210),(HEIGHT+550)),add("system_files/add.png",SizeS,k,(LENGTH+210),(HEIGHT+350)),reset("system_files/clear.png",SizeS,k,(LENGTH+210),(HEIGHT+450)),hint("system_files/hint.png",Vector2f(30,30),k,55,55);
	comand cent("system_files/cent.png",SizeS,k,(50),(HEIGHT+450)),col("system_files/col.png",SizeS,k,(50),(HEIGHT+550));
	texture_list t10(k);
	col.button.setFillColor(Color::Red);
	cent.button.setFillColor(Color::Red);
	RectangleShape alarm(Vector2f(500,100)*k);
	alarm.setPosition(WIDTH/2,WIDTH/2);
	alarm.setTexture(&r1);
	alarm.setOrigin(250,50);
	t10.load(list_ptr);
	hint.button.setOutlineThickness(4.5*k);
	RectangleShape rules(Vector2f(500,750)*k);
	rules.setPosition(50*k,50*k);
	rules.setTexture(&r);
	RectangleShape rect(Vector2f(480,1100)*k);
	rect.setPosition((LENGTH2-240)*k,-10);//нужно добавить
	rect.setFillColor(Color::Black);//нужно добавить
	rect.setOutlineThickness(3);
	Clock clock;
	Vector2i movl(0,0);
	double blo = 1;
	double time_c = 1;
	double blorp = 1;
	int snd = 0;
	int i = 1;
	int fl = 0;
	int hnt = 0;
	int cn = 0;
	int blip = 0;
	ai = 0;
	Text text2;
	Font font;
	font.loadFromFile("arial.ttf");
	object_list ol(k,font);
	data block (k,font);
	title name(k,1,&font);
	name.name = atl.name;
	title name1(k,0,&font);
	Atlas_node tmp;
	Vector2i p; 
	block.origin();
	ol.list(&atl);
	Event event;
	Phase_space* attr = attr_creator(&atl); // Проверка пустого атласа и атласа с одним объектом (Alex: done)
	ol.scroll(0);
	t10.scroll(0);
	range=atl.get_max();
	Motion(&atl, 0, 0, WIDTH, 0.01e-19, attr, range/WIDTH*2);	
	while (i) 
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = T_SCALE * time;	
		p=Mouse::getPosition(*window);
		shape->setPosition(p.x,p.y);
		while (window->pollEvent(event))
		{	
			if ((event.type == Event::MouseButtonPressed)&&(event.mouseButton.button == Mouse::Left)&& p.x < WIDTH && !hint.pressed(p,k)&& !col.pressed(p,k)&& !cent.pressed(p,k))
			{
				movl.x = -(p.x-WIDTH/2);
				movl.y = -(p.y-WIDTH/2);
			}
			if(event.type == Event::KeyPressed && event.key.code == Keyboard::Right)
			{
				t10.scroll(1);
			}
			if(event.type == Event::KeyPressed && event.key.code == Keyboard::Left)
			{
				t10.scroll(-1);
			}
			if(event.type == Event::KeyPressed && event.key.code == Keyboard::Down)
			{
				ol.scroll(-1);
			}
			if(event.type == Event::KeyPressed && event.key.code == Keyboard::Up)
			{
				ol.scroll(1);
			}
			if(event.type == Event::KeyPressed && event.key.code == Keyboard::LControl)
			{
				if(ol.active)
				{ 	
					atl.remove();
					attr_remove(attr, &atl);
					ol.remove();
					ol.scroll(0);
					range=atl.get_medium();
					if (cn) range = atl.get_medium(movl);
				}
			}
			if((event.type == Event::MouseButtonPressed)&&(event.mouseButton.button == Mouse::Right))
			{
				ol.check2(p,&atl);
			}
			if((event.type == Event::MouseButtonPressed)&&(event.mouseButton.button == Mouse::Left)) 
			{
				block.step_check(p,k);
				name.check(p,k);
				name1.check(p,k);
				t10.check(p);
				ol.check(p,&atl);
				if (add.pressed(p,k) && name.name.size())
				{
									block.last_update();
					if(block.first->all_res && block.first->next->all_res)
					{
						blorp = pow(1.1,blip);
						planet = new Celestial_Body((double)(block.first->next->next->all_res),(double)(block.first->next->next->next->all_res),(double)(block.first->next->next->next->next->all_res),(double)(block.first->next->next->next->next->next->all_res),(double)(block.first->next->next->all_res)*0,(double)(block.first->next->next->next->all_res)*0,(double)(block.first->next->all_res)*blorp,(double)(block.first->all_res),t10.path,name1.name);
						atl.add(planet);
						atl.last->avatar.setPosition(atl.last->body.x,atl.last->body.y);
						obj = new object(atl.last,&(ol.font),k);
						ol.add(obj);
						attr_add(attr, planet); // добавление в пустой атлас (Alex: done)
						delete planet;
						ol.scroll(0);
						range=atl.get_medium();
						if (cn) range = atl.get_medium(movl);
					}
				}
				if (save.pressed(p,k) && name1.name.size())
				{
					save_system(atl,name.name);
				}
				if (reset.pressed(p,k) && name1.name.size())
				{
					block.reset();
					name1.reset();
				}
				if (hint.pressed(p,k))
				{
					switch (hnt)
					{
						case (0) :
						{
							hnt=1;
							break;
						}
						case (1):
						{
							hnt=0;
							break;
						}
					}
				}
				if (col.pressed(p,k))
				{
					switch (ai)
					{
						case (0) :
						{
							ai=1;
							col.button.setFillColor(Color::Green);
							break;
						}
						case (1):
						{
							ai=0;
							col.button.setFillColor(Color::Red);
							break;
						}
					}
				}
				if (cent.pressed(p,k))
				{
					switch (cn)
					{
						case (0) :
						{
							cn=1;
							cent.button.setFillColor(Color::Green);
							break;
						}
						case (1):
						{
							cn=0;
							cent.button.setFillColor(Color::Red);
							break;
						}
					}
				}
				if (fatal_error)
				{
					i = 0;
				}
			}
			if(name.flag==0 && name1.flag==0 &&event.type == Event::KeyPressed && event.key.code == Keyboard::X)
			{
				blo*=1.1;
				blorp*=1/blo*0.05+1.2; 
				tmp = atl.first;
				while(tmp)
				{
					tmp->avatar.setScale(1.3945*pow(blo, -0.222),1.3945*pow(blo, -0.222));
					tmp=tmp->next;
				}
			}
			if(name.flag==0 && name1.flag==0 &&event.type == Event::KeyPressed && event.key.code == Keyboard::Z)
			{
				blo*=1/1.1;
				blorp*=1/blo*0.05+1.2; 
				tmp = atl.first;
				while(tmp)
				{
					tmp->avatar.setScale(1.3945*pow(blo, -0.222),1.3945*pow(blo, -0.222));
					tmp=tmp->next;
				}
			}
			
			if(name.flag==0 && name1.flag==0 &&event.type == Event::KeyPressed && event.key.code == Keyboard::A)
			{
				if (time_c <= 5) time_c*=1.1;
			}
			if(name.flag==0 && name1.flag==0 &&event.type == Event::KeyPressed && event.key.code == Keyboard::S)
			{
				if (time_c >= 0.5) time_c*=1/1.1;
			}
			
			if(event.type == Event::Closed || 
			(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
			i=0;
			if(name.flag==0 && name1.flag==0 && event.type == Event::KeyPressed && event.key.code == Keyboard::P)
			{	
				switch (fl)
					{
						case (0) :
						{
							fl=1;
							break;
						}
						case (1):
						{
							fl=0;
							break;
						}
					}
			}
			input(&name,event);
			input(&name1,event);
			input(&block,&event);
			block.update();
			name.update();
			name1.update();
		}
		if(cn)
		{
			movl.x = atl.mass_center(WIDTH,range,blo).x;
			movl.y = atl.mass_center(WIDTH,range,blo).y;
		}
		if(mode == 1)
		{
			if(fl&&!fatal_error) Motion(&atl, (time_c * time), 0.05 * (time_c * time), WIDTH, 0.01e-19, attr, range/WIDTH*0.001,range,movl,blo);
			if(!fl&&!fatal_error) Motion(&atl, 0, 0, WIDTH, 0.01e-19, attr, range/WIDTH*0.001,range,movl,blo);
		}
		if(mode == 0)
		{
			if(fl&&!fatal_error) Motion(&atl, (time_c * time), 0.05 * (time_c * time), WIDTH, attr, range/WIDTH*0.001,range,movl,blo);
			if(!fl&&!fatal_error) Motion(&atl, 0, 0, WIDTH,  attr, range/WIDTH*0.001,range,movl,blo);
		}
		window->clear();
		window->draw(bg);
		draw(&atl, window);
		window->draw(rect);
		draw(&ol, window);
		block.draw(window);
		name.draw(window);
		name1.draw(window);
		draw(&t10,window);
		if (fatal_error) 
		{
			window->draw(alarm);
			snd++;
		}
		if (snd == 1) 
		{
			furi->pause();;
			me.play();
			snd ++;
		}
		if (hnt) window->draw(rules);
		window->draw(save.button);
		window->draw(add.button);
		window->draw(reset.button);
		window->draw(hint.button);
		window->draw(col.button);
		window->draw(cent.button);
		window->draw((*shape));
		window->display();
	}
	block.destroy();
	ol.destroy();
	atl.del();
	list_ptr.destroy();
	t10.destroy();
	delete[] attr;
	return 0;
}
