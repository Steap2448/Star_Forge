#define G 6.67408e-11

#include "method.hpp"

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
//
double x(double x_m, double scale)
{
	double res = (x_m * (scale))/(6.084e11) + scale/2;
	return res;
}

double y(double y_m, double scale)
{
	double res = scale/2 - (y_m * scale)/(6.084e11);
	return res;
}

double x_satellite(double x, Celestial_Body* a)
{
	double res = x + a->x;
	return res;
}

double y_satellite(double y, Celestial_Body* a)
{
	double res = y + a->y;
	return res;
}

double v_x_satellite(double v_x, Celestial_Body* a)
{
	double res = v_x + a->v_x;
	return res;
}

double v_y_satellite(double v_y, Celestial_Body* a)
{
	double res = v_y + a->v_y;
	return res;
}
//
double distance(Celestial_Body* a, Celestial_Body* b)
{
	double dist = sqrt((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
	return dist;
}

Phase_vector f(Celestial_Body* a, Atlas* atl, Phase_vector* k, int kn, double step)
{
	double dist;
	Atlas_node tmp = atl->first;
	Phase_vector k_tmp;
	if ((kn == 2)||(kn == 3)) k_tmp = (*k) / 2;
	else k_tmp = (*k);
	Phase_vector res = Phase_vector();
	res.x = ((a -> v_x) + (k_tmp.v_x));
	res.y = ((a -> v_y) + (k_tmp.v_y));
	res.v_x = 0;
	res.v_y = 0;
	int i=0;
	while (tmp != NULL)
	{
		if(!((a->x == (tmp -> body.x))&&(a->y == (tmp -> body.y))))
		{
			i++;
			dist = distance(a, &(tmp->body));
			res.v_x = res.v_x + (G *  tmp->body.Mass * (tmp->body.x - ((a -> x) + (k_tmp.x))) )/(dist * dist * dist);
			res.v_y = res.v_y + (G *  tmp->body.Mass * (tmp->body.y - ((a -> y) + (k_tmp.y))))/(dist * dist * dist);
		}
		tmp = tmp->next;
	}	
	return res;
}

Phase_vector f(Celestial_Body* a, Atlas* atl)
{
	double dist;
	Atlas_node tmp = atl->first;
	Phase_vector res = Phase_vector();
	res.x = (a -> v_x);
	res.y = (a -> v_y);
	res.v_x = 0;
	res.v_y = 0;
	while (tmp != NULL)
	{
		if(!((a->x == (tmp -> body.x))&&(a->y == (tmp -> body.y))))
		{
			dist = distance(a, &(tmp->body));
			res.v_x = res.v_x + (G *  tmp->body.Mass * (tmp->body.x - (a -> x)) )/(dist * dist * dist);
			res.v_y = res.v_y + (G *  tmp->body.Mass * (tmp->body.y - (a -> y)))/(dist * dist * dist);
		}
		tmp = tmp->next;
	}	
	tmp = NULL;
	return res;
}

Phase_vector k1(Celestial_Body* a, Atlas* atl)
{
	return f(a, atl);
}

Phase_vector k2(Celestial_Body* a, Atlas* atl, double step, Phase_vector* k1)
{
	return f(a, atl, k1, 2, step);
}

Phase_vector k3(Celestial_Body* a, Atlas* atl, double step, Phase_vector* k2)
{
	return f(a, atl, k2, 3, step);
}

Phase_vector k4(Celestial_Body* a, Atlas* atl, double step, Phase_vector* k3)
{
	return f(a, atl, k3, 4, step);
}

Phase_vector Movement(Celestial_Body* a, Atlas* atl, double step)
{
	Phase_vector res = Phase_vector();
	Phase_vector k12 = k1(a, atl);
	Phase_vector k22 = k2(a, atl, step, &k12);
	Phase_vector k32 = k3(a, atl, step, &k22);
	Phase_vector k42 = k4(a, atl, step, &k32);
	res = (k12 + (k22 * 2) + (k32 * 2) + k42) * (step / 6);
	return res;
}

Atlas* Motion(Atlas* atl, double t_scale, double step, double scale)
{
	Atlas_node tmp = atl->first;
	int i, step_amount = t_scale / step;
	double last_step = t_scale - step * step_amount;
	Phase_vector mov;
	for (i = 1; i <= step_amount; i++)
	{
		tmp = atl->first;
		while(tmp != NULL)
		{
			mov = Movement(&(tmp->body), atl, step);
			tmp->body = tmp->body+ mov;
			tmp->avatar.setPosition(x(tmp->body.x, scale), y(tmp->body.y, scale));
			tmp = tmp->next; 
		}
	}
	tmp = atl->first;
	if (last_step != 0)
	while(tmp != NULL)
		{
			mov = Movement(&(tmp->body), atl, t_scale - (step * last_step));
			tmp->body = tmp->body+ mov;
			tmp->avatar.setPosition(x(tmp->body.x, scale), y(tmp->body.y, scale));
			tmp = tmp->next; 
		}
		
	return atl;
}

void draw(Atlas* atl, sf::RenderWindow* window)
{
	Atlas_node tmp = atl->first;
	while(tmp != NULL)
	{
		window->draw(tmp->avatar);
		tmp = tmp->next;
	}	
	return;
}

//Paral_sec

void* Movement_paral(void* argument_v)
{
	arg* argument = (arg*) argument_v;
	Celestial_Body* a = argument -> a;
	Atlas* atl = argument -> atlas;
	double step = argument -> step;
	Phase_vector k12 = k1(a, atl);
	Phase_vector k22 = k2(a, atl, step, &k12);
	Phase_vector k32 = k3(a, atl, step, &k22);
	Phase_vector k42 = k4(a, atl, step, &k32);
	argument->res = (k12 + (k22 * 2) + (k32 * 2) + k42) * (step / 6);
	return NULL;
}

Atlas* Motion_paral(Atlas* atl, Pthread_array* pth_adr, double t_scale, double step)
{
	Atlas_node tmp = atl->first;
	Pthread_array pth = *pth_adr;
	int i, step_amount = t_scale / step, l = 0;
	double last_step = t_scale - step * step_amount;
	Phase_vector mov;
	pth.current = 0;
	atl->out();
	for (i = 1; i <= step_amount; i++)
	{
		tmp = atl->first;
		while(tmp != NULL)
		{
			pth.equip(&(tmp->body), step);
			pthread_create(&(pth.thread[pth.current]), NULL, Movement_paral,(void*) &(pth.argument[pth.current]));
			pth.next();
			tmp = tmp -> next;
			l++;
		}
		pth.join();
	}
	tmp = atl->first;
	if (last_step != 0)
	while(tmp != NULL)
		{
			pth.equip(&(tmp->body), last_step);
			pthread_create(&(pth.thread[pth.current]), NULL, Movement_paral, &(pth.argument[pth.current]));
			pth.next();
			tmp = tmp -> next;
			l++;
		}
	pth.join();
	atl->out();	
	return atl;
}

void Atlas::move(double scale)
{
	Atlas_node tmp = first; 
	while (tmp != NULL)
	{
		tmp->body += tmp->body.mov;
		tmp->avatar.setPosition(x(tmp->body.x, scale), y(tmp->body.y, scale));
		tmp = tmp -> next;
	}
	return;
}

void* Motion_paral_mod(void* argument_v)
{
	pthread_mutex_lock(&m);
	arg_mod* argument = (arg_mod*) argument_v;
	Atlas* atl = argument->atlas;
	double t_scale = argument->t_scale;
	double step = argument->step;
	Atlas_node tmp = argument->start;
	int i, step_amount = t_scale / step;
	double last_step = t_scale - step * step_amount;
	for (i = 1; i <= step_amount; i++)
	{
		tmp = argument->start;
		while(tmp != argument->finish)
		{
			tmp->body.mov = Movement(&(tmp->body), atl, step);
			tmp = tmp->next; 
		}
		tmp->body.mov = Movement(&(tmp->body), atl, step);
	}
	tmp = argument->start;
	if (last_step != 0)
	while(tmp != argument->finish)
		{
			tmp->body.mov = Movement(&(tmp->body), atl, t_scale - (step * last_step));
			tmp = tmp->next; 
		}
	tmp->body.mov = Movement(&(tmp->body), atl, t_scale - (step * last_step));
	pthread_mutex_unlock(&m);
	pthread_exit(NULL);
	return atl;
}

void* test(void* a)
{
	pthread_mutex_lock(&m);
	std::cout<<"Hello world!\n";
	pthread_mutex_unlock(&m);
	pthread_exit(0);
}

