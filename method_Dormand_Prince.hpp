#ifndef METHOD_DORMAN_PRINCE
#define METHOD_DORMAN_PRINCE

double b[9][7] = {  {0,              0,               0,               0,            0,                 0,            0},
					{1/5.0,          0,               0,               0,            0,                 0,            0},
					{30.0/40.0,      9.0/40.0,        0,               0,            0,                 0,            0},  
					{44.0/45.0,      -56.0/15.0,      32.0/9.0,        0,            0,                 0,            0}, 
					{19372.0/6561.0, -25360.0/2187.0, 64448.0/6561.0,  -212.0/729.0, 0,                 0,            0}, 
					{9017.0/3168.0,  -355.0/33.0,     -46732.0/5247.0, 49.0/176.0,   -5103.0/18656.0,   0,            0},
					{35.0/384.0,     0,               500.0/1113.0,    125.0/192.0,  -2187.0/6784.0,    11.0/84.0,    0},
					{35.0/384.0,     0,               50.0/1113.0,     125.0/192.0,  -2187.0/6784.0,    11.0/84.0,    0},
					{5179.0/57600.0, 0,               7571.0/16695.0,  393.0/640.0,  -92097.0/339200.0, 187.0/2100.0, 1.0/40.0}};

typedef struct _Phase_space_node
{
	Phase_vector body;
	_Phase_space_node* next;
	double mass;
	int order;
} *Phase_space_node, Phase_space_node_el;

class Phase_space
{
	public:
	int amount;
	Phase_space_node first;
	
	Phase_space()
	{
		amount = 0;
		first = NULL;
	}
	
	Phase_space(int a)
	{
		amount = 0;
		int i = 0;
		if (a == 0) 
		{
			*this = Phase_space();
			return;
		}
		Phase_space_node tmp;
		while(amount != a)
		{
			if (amount == 0)
			{
				first = new Phase_space_node_el;
				first -> body = Phase_vector();
				first -> next = NULL;
				first -> mass = 0;
				first -> order = i;
				tmp = first;
				amount++;
				i++;
			}
			else
			{
				tmp -> next = new Phase_space_node_el;
				tmp = tmp -> next;
				tmp -> body = Phase_vector();
				tmp -> mass = 0;
				tmp -> next = NULL;
				tmp -> order = i;
				amount ++;
				i++;
			}
		}
	}
	
	Phase_space(Atlas* atl)
	{
		if (atl->amount == 0)
		{
			*this = Phase_space();
			return;
		}
		int i = 0;
		Phase_space_node tmp;
		Atlas_node tmp2 = atl->first;
		amount = 0;
		while(tmp2 != NULL)
		{
			if (amount == 0)
			{
				first = new Phase_space_node_el;
				first -> body = Phase_vector(tmp2->body.x, tmp2->body.y, tmp2->body.v_x, tmp2->body.v_y);
				first -> next = NULL;
				first -> mass = tmp2->body.Mass;
				tmp = first;
				first -> order = i;
				tmp2 = tmp2 -> next;
				amount++;
				i++;
			}
			else
			{
				tmp -> next = new Phase_space_node_el;
				tmp = tmp -> next;
				tmp -> body = Phase_vector(tmp2->body.x, tmp2->body.y, tmp2->body.v_x, tmp2->body.v_y);
				tmp -> mass = tmp2->body.Mass;
				tmp -> next = NULL;
				tmp2 = tmp2 -> next;
				tmp -> order = i;
				amount ++;
				i++;
			}
		}
	}
	
	Phase_space(const Phase_space& other)
	{
		if (other.amount == 0)
		{
			*this = Phase_space();
			return;
		}
		Phase_space_node tmp, tmp2 = other.first;
		amount = 0;
		while(tmp2 != NULL)
		{
			if (tmp2 == other.first)
			{
				first = new Phase_space_node_el;
				first -> body = Phase_vector(tmp2->body.x, tmp2->body.y, tmp2->body.v_x, tmp2->body.v_y);
				first -> next = NULL;
				first -> mass = tmp2->mass;
				first -> order = tmp2->order;
				tmp = first;
				tmp2 = tmp2 -> next;
				amount++;
			}
			else
			{
				tmp -> next = new Phase_space_node_el;
				tmp = tmp -> next;
				tmp -> body = Phase_vector(tmp2->body.x, tmp2->body.y, tmp2->body.v_x, tmp2->body.v_y);
				tmp -> mass = tmp2->mass;
				tmp -> next = NULL;
				tmp -> order = tmp2->order;
				tmp2 = tmp2 -> next;
				amount ++;
			}
		}
	}
	
	void operator +=(Phase_space a);
	void operator -=(Phase_space a);
	Phase_space operator +(Phase_space a);
	Phase_space operator -(Phase_space a);
	Phase_space operator *(double a);
	Phase_space operator /(double a);
	void operator =(Phase_space a);
	void operator =(Phase_space* a);
	void operator *=(double a);
	
	void save(Atlas* atl, double scale)
	{
		if (atl->amount != amount) return;
		Atlas_node tmp = atl -> first;
		Phase_space_node tmp1 = first;
		while(tmp1 != NULL)
		{
			tmp -> body.x = tmp1 -> body.x;
			tmp -> body.y = tmp1 -> body.y;
			tmp->avatar.setPosition(x(tmp->body.x, scale), y(tmp->body.y, scale));
			tmp -> body.v_x = tmp1 -> body.v_x;
			tmp -> body.v_y = tmp1 -> body.v_y;
			tmp = tmp -> next;
			tmp1 = tmp1 -> next;
		} 
		return;
	}
	
	void add(Celestial_Body* a)
	{
		Phase_space_node tmp = first;
		if (tmp == NULL)
		{
			tmp = new Phase_space_node_el;
			tmp -> body = Phase_vector(a->x, a->y, a->v_x, a->v_y);
			tmp -> next = NULL;
			tmp -> mass = a->Mass;
			tmp -> order = 0;
			first = tmp;
			amount = 1;
			return;
		}
		while (tmp -> next != NULL) tmp = tmp -> next;
		int i = tmp -> order;
		tmp -> next = new Phase_space_node_el;
		tmp = tmp -> next;
		tmp -> body = Phase_vector(a->x, a->y, a->v_x, a->v_y);
		tmp -> next = NULL;
		tmp -> mass = a->Mass;
		tmp -> order = (i+1);
		amount++;
		return;
	}
	
	void add()
	{
		Phase_space_node tmp = first;
		if (tmp == NULL)
		{
			tmp = new Phase_space_node_el;
			tmp -> body = Phase_vector();
			tmp -> next = NULL;
			tmp -> mass = 0;
			tmp -> order = 0;
			amount = 1;
			first = tmp;
			return;
		}
		while (tmp -> next != NULL) tmp = tmp -> next;
		int i = tmp -> order;
		tmp -> next = new Phase_space_node_el;
		tmp = tmp -> next;
		tmp -> body = Phase_vector();
		tmp -> next = NULL;
		tmp -> mass = 0;
		tmp -> order = (i+1);
		amount++;
		return;
	}
	
	
	~Phase_space()
	{
		Phase_space_node tmp1 = first;
		while(tmp1 != NULL)
		{
			Phase_space_node tmp2 = tmp1;
			tmp1 = tmp1 -> next;
			delete tmp2;
		}
	}
	
	void out()
	{
		std::cout<<amount<<"\n";
		Phase_space_node tmp = first;
		while(tmp != NULL)
		{ 
			std::cout<<tmp->body.x<<" "<<tmp->body.y<<" "<<tmp->body.v_x<<" "<<tmp->body.v_y<<" Mass "<<tmp->mass<<"\n";
			tmp = tmp -> next;
		}
		return;
	}
	/*void del()
	{
		delete object;
		delete mass;
	}*/
};
//In case the first method.hpp won`t be used
/*double x(double x_m, double scale);

double y(double y_m, double scale);

double x_satellite(double x, Celestial_Body* a);

double y_satellite(double y, Celestial_Body* a);

double v_x_satellite(double v_x, Celestial_Body* a);

double v_y_satellite(double v_y, Celestial_Body* a);*/

double distance(double x1, double y1, double x2, double y2);

Phase_space* f(Phase_space k, Phase_space* res_v);

double error(Phase_space k);

Phase_space* Motion(Atlas* atl, double t_scale, double step, double scale, double mistake, Phase_space* attr);

Phase_space* attr_creator(Atlas* atl);

Phase_space* attr_add(Phase_space* attr, Celestial_Body* a);

#endif


