#define G 6.67408e-11

#include "method_Dorman_Prince.hpp"

void Phase_space::operator +=(Phase_space a)
{
	for (int i = 0; i < amount; i ++)
	{
		if (a.amount != amount) return;
		object[i].x += a.object[i].x;
		object[i].y += a.object[i].y;
		object[i].v_x += a.object[i].v_x;
		object[i].v_y += a.object[i].v_y;
	} 
	return;
}
void Phase_space::operator -=(Phase_space a)
{
	if (a.amount != amount) return;
	for (int i = 0; i < amount; i ++)
	{
		object[i].x -= a.object[i].x;
		object[i].y -= a.object[i].y;
		object[i].v_x -= a.object[i].v_x;
		object[i].v_y -= a.object[i].v_y;
	}	
	return;
}

Phase_space Phase_space::operator +(Phase_space a)
{
	if (a.amount != amount) return Phase_space();
	Phase_space res = Phase_space(a.amount);
	for (int i = 0; i < amount; i ++)
		{
			res.object[i].x = object[i].x + a.object[i].x;
			res.object[i].y = object[i].y + a.object[i].y;
			res.object[i].v_x = object[i].v_x + a.object[i].v_x;
			res.object[i].v_y = object[i].v_y + a.object[i].v_y;
			res.mass[i] = a.mass[i];
		}
	return res;
}

Phase_space Phase_space::operator -(Phase_space a)
{
	if (a.amount != amount) return Phase_space();
	Phase_space res = Phase_space(a.amount);
	for (int i = 0; i < amount; i ++)
		{
			res.object[i].x = object[i].x - a.object[i].x;
			res.object[i].y = object[i].y - a.object[i].y;
			res.object[i].v_x = object[i].v_x - a.object[i].v_x;
			res.object[i].v_y = object[i].v_y - a.object[i].v_y;
			res.mass[i] = a.mass[i];
		}
	return res;
}

void Phase_space::operator *=(double a)
{
	for (int i = 0; i < amount; i ++)
	{
		object[i].x *= a;
		object[i].y *= a;
		object[i].v_x *= a;
		object[i].v_y *= a;
	}	
	return;
}

void Phase_space::operator =(Phase_space a)
{
	if (a.amount != amount) return;
	for (int i = 0; i < amount; i ++)
	{
		object[i].x = a.object[i].x;
		object[i].y = a.object[i].y;
		object[i].v_x = a.object[i].v_x;
		object[i].v_y = a.object[i].v_y;
		mass[i] = a.mass[i];
	}
	return;
}

Phase_space Phase_space::operator *(double a)
{
	Phase_space res = Phase_space(amount);
	res.amount = amount;
	for (int i = 0; i < amount; i ++)
		{
			res.object[i].x = object[i].x * a;
			res.object[i].y = object[i].y * a;
			res.object[i].v_x = object[i].v_x * a;
			res.object[i].v_y = object[i].v_y * a;
			res.mass[i] = mass[i];
		}
	return res;
	
}
Phase_space Phase_space::operator /(double a)
{
	Phase_space res = Phase_space(amount);
	res.amount = amount;
	for (int i = 0; i < amount; i ++)
		{
			res.object[i].x = object[i].x / a;
			res.object[i].y = object[i].y / a;
			res.object[i].v_x = object[i].v_x / a;
			res.object[i].v_y = object[i].v_y / a;
			res.mass[i] = mass[i];
		}
	return res;
}/*
//In case the first method.hpp won`t be used
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

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
}*/
//
double distance(double x1, double y1, double x2, double y2)
{
	double dist = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	return dist;
}


Phase_space* f(Phase_space k, Phase_space* res)
{
	double dist;
	for (int i = 0; i < k.amount; i ++)
		{
			res->object[i].x = k.object[i].v_x;
			res->object[i].y = k.object[i].v_y;
			res->object[i].v_x = 0;
			res->object[i].v_y = 0;
			res->mass[i] = k.mass[i];
		}
	int i = 0, j = 0;
	for(i = 0; i < k.amount; i ++)
	{
		for(j = 0; j < k.amount; j++)
		{
			if (j != i)
			{
				dist = distance(k.object[i].x, k.object[i].y, k.object[j].x, k.object[j].y);
				res->object[i].v_x += (G * k.mass[j] *(k.object[j].x - k.object[i].x)/(dist * dist * dist)) ;
				res->object[i].v_y += (G * k.mass[j] *(k.object[j].y - k.object[i].y)/(dist * dist * dist)) ;
			}
		}
	}
	return res;
}

Phase_space* k1(Phase_space k, Phase_space* res_v)
{
	return f(k, res_v);
}

Phase_space* k2(Phase_space k, Phase_space k1, Phase_space* res_v)
{
	return f(k + k1/5, res_v);
}

Phase_space* k3(Phase_space k, Phase_space k1, Phase_space k2, Phase_space* res_v)
{
	return f(k + (k1 * 3/40) + (k2 * 9/40), res_v);
}

Phase_space* k4(Phase_space k, Phase_space k1, Phase_space k2, Phase_space k3, Phase_space* res_v)
{
	return f(k+(k1 * 44/45)+(k2 * -56/15)+(k3 * 32/9), res_v);
}

Phase_space* k5(Phase_space k, Phase_space k1, Phase_space k2, Phase_space k3, Phase_space k4, Phase_space* res_v)
{
	return f(k+(k1 * 19372/6561)+(k2 * -25360/2187)+(k3 * 64448/6561)+(k4 * -212/729), res_v);
}

Phase_space* k6(Phase_space k, Phase_space k1, Phase_space k2, Phase_space k3, Phase_space k4, Phase_space k5, Phase_space* res_v)
{
	return f(k+(k1 * 9017/3168)+(k2 * -355/33)+(k3 * -46732/5247)+(k4 * 49/176)+(k5 * -5103/18656), res_v);
}

Phase_space* k7(Phase_space k, Phase_space k1, Phase_space k3, Phase_space k4, Phase_space k5, Phase_space k6, Phase_space* res_v)
{
	return f(k+(k1 * 35/384)+(k3 * 500/1113)+(k4 * 125/192)+(k5 * -2187/6784)+(k6 * 11/84), res_v);
}

double error(Phase_space k)
{
	double res = 0, err = 0;
	int i = 0;
	for(i = 0; i < k.amount; i ++)
	{
		if (abs(k.object[i].x) > err) err = abs(k.object[i].x);
	}
	for(i = 0; i < k.amount; i ++)
	{
		if (abs(k.object[i].y) > err) err = abs(k.object[i].y);
	}
	for(i = 0; i < k.amount; i ++)
	{
		if (abs(k.object[i].v_x) > err) err = abs(k.object[i].v_x);
	}
	for(i = 0; i < k.amount; i ++)
	{
		if (abs(k.object[i].v_y) > err) err = abs(k.object[i].v_y);
	}
	return err;
}

Phase_space* Motion(Phase_space* k_a, Atlas* atl, double t_scale, double step, double scale, double mistake, Phase_space* attr)
{
	double time = step, step_ad = step, err, s;
	int i;
	attr[0] = *k_a;
	while(time < t_scale)
	{
		k1(attr[0], &(attr[1]));
		k2(attr[0], attr[1], &(attr[2]));
		k3(attr[0], attr[1], attr[2], &(attr[3]));
		k4(attr[0], attr[1], attr[2], attr[3], &(attr[4]));
		k5(attr[0], attr[1], attr[2], attr[3], attr[4], &(attr[5]));
		k6(attr[0], attr[1], attr[2], attr[3], attr[4], attr[5], &(attr[6]));
		k7(attr[0], attr[1], attr[3], attr[4], attr[5], attr[6], &(attr[7]));
		for(i = 1; i <= 7; i++) attr[i] *= step_ad;
		attr[8] = ((attr[1] * 35/384)+(attr[3] * 50/1113)+(attr[4] * 125/192)+(attr[5] * -2187/6784)+(attr[6] * 11/84));
		attr[9] = ((attr[1] * 5179/57600)+(attr[3] * 7571/16695)+(attr[4] * 393/640)+(attr[5] * -92097/339200)+(attr[6] * 187/2100)+(attr[7] * 1/40));
		err = error(attr[8] - attr[9]);
		s = pow(mistake * step/(2*1), 0.2);
		attr[0] += attr[8];
		time += step_ad;
		for (int i = 0; i < k_a->amount; i ++)
		{
			k_a -> object[i].x = attr[0].object[i].x;
			k_a -> object[i].y = attr[0].object[i].y;
			k_a -> object[i].v_x = attr[0].object[i].v_x;
			k_a -> object[i].v_y = attr[0].object[i].v_y;
			k_a->mass[i] = attr[0].mass[i];
		}
		if (step_ad * s > step) step_ad = step;
		else if (step_ad * s < step * 0.0001) step_ad = step * 0.0001;
		
	}
	attr[0].save(atl, scale);
	
	return k_a;
}


