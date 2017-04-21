#ifndef METHOD_DORMAN_PRINCE
#define METHOD_DORMAN_PRINCE

class Phase_space
{
	public:
	int amount;
	Phase_vector* object;
	double* mass;
	
	Phase_space()
	{
		amount = 0;
		object = new Phase_vector[amount];
		for(int i = 0; i < amount; i++) object[i] = Phase_vector();
		mass = new double[amount];
	}
	
	Phase_space(int a)
	{
		amount = a;
		object = new Phase_vector[amount];
		for(int i = 0; i < amount; i++) object[i] = Phase_vector();
		mass = new double[amount];
	}
	
	Phase_space(const Phase_space& other)
	{
		amount = other.amount;
		object = new Phase_vector[amount];
		for(int i = 0; i < amount; i++) object[i] = Phase_vector();
		mass = new double[amount];
		for (int i = 0; i < amount; i ++)
		{
			object[i].x = other.object[i].x;
			object[i].y = other.object[i].y;
			object[i].v_x = other.object[i].v_x;
			object[i].v_y = other.object[i].v_y;
			mass[i] = other.mass[i];
		} 
	}
	
	void operator +=(Phase_space a);
	void operator -=(Phase_space a);
	Phase_space operator +(Phase_space a);
	Phase_space operator -(Phase_space a);
	Phase_space operator *(double a);
	Phase_space operator /(double a);
	void operator =(Phase_space a);
	void operator *=(double a);
	void load(Atlas* atl)
	{
		if (atl->amount != amount) return;
		Atlas_node tmp = atl -> first;
		for (int i = 0; i < amount; i ++)
		{
			object[i].x = tmp -> body.x;
			object[i].y = tmp -> body.y;
			object[i].v_x = tmp -> body.v_x;
			object[i].v_y = tmp -> body.v_y;
			mass[i] = tmp -> body.Mass;
			tmp = tmp -> next;
		} 
		return;
	}
	void save(Atlas* atl, double scale)
	{
		if (atl->amount != amount) return;
		Atlas_node tmp = atl -> first;
		for (int i = 0; i < amount; i ++)
		{
			tmp -> body.x = object[i].x;
			tmp -> body.y = object[i].y;
			tmp->avatar.setPosition(x(tmp->body.x, scale), y(tmp->body.y, scale));
			tmp -> body.v_x = object[i].v_x;
			tmp -> body.v_y = object[i].v_y;
			tmp = tmp -> next;
		} 
		return;
	}
	
	
	~Phase_space()
	{
		if (((object != NULL)&&(mass != NULL))&&(amount != 0))
		{
			delete[] object;
			delete[] mass;
		}
	}
	
	void out()
	{
		std::cout<<amount<<"\n";
		for(int i = 0; i < amount; i++) std::cout<<object[i].x<<" "<<object[i].y<<" "<<object[i].v_x<<" "<<object[i].v_y<<" Mass "<<mass[i]<<"\n";
		return;
	}
	void del()
	{
		delete object;
		delete mass;
	}
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

Phase_space* k1(Phase_space k, Phase_space* res_v);

Phase_space* k2(Phase_space k, Phase_space k1, Phase_space* res_v);

Phase_space* k3(Phase_space k, Phase_space k1, Phase_space k2, Phase_space* res_v);

Phase_space* k4(Phase_space k, Phase_space k1, Phase_space k2, Phase_space k3, Phase_space* res_v);

Phase_space* k5(Phase_space k, Phase_space k1, Phase_space k2, Phase_space k3, Phase_space k4, Phase_space* res_v);

Phase_space* k6(Phase_space k, Phase_space k1, Phase_space k2, Phase_space k3, Phase_space k4, Phase_space k5, Phase_space* res_v);

Phase_space* k7(Phase_space k, Phase_space k1, Phase_space k3, Phase_space k4, Phase_space k5, Phase_space k6, Phase_space* res_v);

double error(Phase_space k);

Phase_space* Motion(Phase_space* k_a, Atlas* atl, double t_scale, double step, double scale, double mistake, Phase_space* attr);

#endif


