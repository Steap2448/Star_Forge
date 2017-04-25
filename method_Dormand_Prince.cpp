#define Gi 6.67408e-11

#include "method_Dormand_Prince.hpp"

void Phase_space::operator +=(Phase_space a)
{
	if (amount != a.amount) return;
	Phase_space_node tmp1 = first, tmp2 = a.first;
	while(tmp2 != NULL)
	{
		tmp1->body.x += tmp2->body.x;
		tmp1->body.y += tmp2->body.y;
		tmp1->body.v_x += tmp2->body.v_x;
		tmp1->body.v_y += tmp2->body.v_y;
		tmp1 = tmp1 -> next;
		tmp2 = tmp2 -> next;
	} 
	return;
}
void Phase_space::operator -=(Phase_space a)
{
	if (amount != a.amount) return;
	Phase_space_node tmp1 = first, tmp2 = a.first;
	while(tmp2 != NULL)
	{
		tmp1->body.x -= tmp2->body.x;
		tmp1->body.y -= tmp2->body.y;
		tmp1->body.v_x -= tmp2->body.v_x;
		tmp1->body.v_y -= tmp2->body.v_y;
		tmp1 = tmp1 -> next;
		tmp2 = tmp2 -> next;
	}	
	return;
}

Phase_space Phase_space::operator +(Phase_space a)
{
	if (amount != a.amount) return Phase_space();
	Phase_space res = Phase_space(amount);
	Phase_space_node tmp1 = first, tmp2 = a.first, tmp = res.first;
	while(tmp2 != NULL)
	{
		tmp->body.x = tmp1->body.x + tmp2->body.x;
		tmp->body.y = tmp1->body.y + tmp2->body.y;
		tmp->body.v_x = tmp1->body.v_x + tmp2->body.v_x;
		tmp->body.v_y = tmp1->body.v_y + tmp2->body.v_y;
		tmp-> mass = tmp1->mass;
		tmp = tmp -> next;
		tmp1 = tmp1 -> next;
		tmp2 = tmp2 -> next;
	}
	return res;
}

Phase_space Phase_space::operator -(Phase_space a)
{
	if (amount != a.amount) return Phase_space();
	Phase_space res = Phase_space(amount);
	Phase_space_node tmp1 = first, tmp2 = a.first, tmp = res.first;
	while(tmp2 != NULL)
	{
		tmp->body.x = tmp1->body.x - tmp2->body.x;
		tmp->body.y = tmp1->body.y - tmp2->body.y;
		tmp->body.v_x = tmp1->body.v_x - tmp2->body.v_x;
		tmp->body.v_y = tmp1->body.v_y - tmp2->body.v_y;
		tmp-> mass = tmp1->mass;
		tmp = tmp -> next;
		tmp1 = tmp1 -> next;
		tmp2 = tmp2 -> next;
	}
	return res;
}

void Phase_space::operator *=(double a)
{
	Phase_space_node tmp1 = first;
	while(tmp1 != NULL)
	{
		tmp1->body.x *= a;
		tmp1->body.y *= a;
		tmp1->body.v_x *= a;
		tmp1->body.v_y *= a;
		tmp1 = tmp1 -> next;
	}
	return;
}

void Phase_space::operator =(Phase_space a)
{
	if (a.amount != amount) return;
	Phase_space_node tmp1 = first, tmp2 = a.first;
	while(tmp2 != NULL)
	{
		tmp1->body.x = tmp2->body.x;
		tmp1->body.y = tmp2->body.y;
		tmp1->body.v_x = tmp2->body.v_x;
		tmp1->body.v_y = tmp2->body.v_y;
		tmp1->mass = tmp2->mass;
		tmp1 = tmp1 -> next;
		tmp2 = tmp2 -> next;
	}
	return;
}

void Phase_space::operator =(Phase_space* a)
{
	if (a->amount != amount) return;
	Phase_space_node tmp1 = first, tmp2 = a->first;
	while(tmp2 != NULL)
	{
		tmp1->body.x = tmp2->body.x;
		tmp1->body.y = tmp2->body.y;
		tmp1->body.v_x = tmp2->body.v_x;
		tmp1->body.v_y = tmp2->body.v_y;
		tmp1->mass = tmp2->mass;
		tmp1 = tmp1 -> next;
		tmp2 = tmp2 -> next;
	}
	return;
}

Phase_space Phase_space::operator *(double a)
{
	Phase_space res = Phase_space(amount);
	Phase_space_node tmp1 = first, tmp = res.first;
	while(tmp1 != NULL)
	{
		tmp->body.x = tmp1->body.x * a;
		tmp->body.y = tmp1->body.y * a;
		tmp->body.v_x = tmp1->body.v_x * a;
		tmp->body.v_y = tmp1->body.v_y * a;
		tmp-> mass = tmp1->mass;
		tmp = tmp -> next;
		tmp1 = tmp1 -> next;
	}
	return res;
	
}
Phase_space Phase_space::operator /(double a)
{
	Phase_space res = Phase_space(amount);
	Phase_space_node tmp1 = first, tmp = res.first;
	while(tmp1 != NULL)
	{
		tmp->body.x = tmp1->body.x / a;
		tmp->body.y = tmp1->body.y / a;
		tmp->body.v_x = tmp1->body.v_x / a;
		tmp->body.v_y = tmp1->body.v_y / a;
		tmp-> mass = tmp1->mass;
		tmp = tmp -> next;
		tmp1 = tmp1 -> next;
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
	Phase_space_node tmp1 = k.first, tmp2 = k.first;
	Phase_space_node tmp = res->first;
	while (tmp1 != NULL)
		{
			tmp->body.x = tmp1->body.v_x;
			tmp->body.y = tmp1->body.v_y;
			tmp->body.v_x = 0;
			tmp->body.v_y = 0;
			tmp->mass = tmp1->mass;
			tmp = tmp -> next;
			tmp1 = tmp1 -> next;
		}
	tmp1 = k.first;
	tmp = res->first;
	while (tmp1 != NULL)
	{
		while (tmp2 != NULL)
		{
			if ((tmp1) != (tmp2))
			{
				dist = distance(tmp1->body.x, tmp1->body.y, tmp2->body.x, tmp2->body.y);
				tmp->body.v_x += (Gi * tmp2->mass *(tmp2->body.x - tmp1->body.x)/(dist * dist * dist)) ;
				tmp->body.v_y += (Gi * tmp2->mass *(tmp2->body.y - tmp1->body.y)/(dist * dist * dist)) ;
				tmp2 = tmp2 -> next;
			}
			else tmp2 = tmp2 -> next;
		}
		tmp1 = tmp1 -> next;
		tmp = tmp -> next;
		tmp2 = k.first;
	}
	return res;
}

double error(Phase_space k)
{
	double res = 0, err1 = 0, err2 = 0, err;
	int i = 0;
	Phase_space_node tmp = k.first;
	while(tmp != NULL)
	{
		if (tmp->body.x > err1) err1 = tmp->body.x;
		if (tmp->body.y > err2) err2 = tmp->body.y;
		tmp = tmp -> next;
	}
	if (err1 > err2) err = err1;
	else err = err2;
	return err;
}

Phase_space* Motion(Atlas* atl, double t_scale, double step, double scale, double mistake, Phase_space* attr)//Correct exeptions
{
	double time = step, step_ad = step, err, s;
	if (atl-> amount <= 1) 
	{
		if (atl -> amount == 1) attr[0].save(atl, scale);
		return &attr[0];
	}
	int i;
	Phase_space_node tmp1, tmp2;
	while(time < t_scale)
	{
		f(attr[0], &(attr[1]));
		f(attr[0] + attr[1] * b[1][0], &(attr[2]));
		f(attr[0] + attr[1] * b[2][0] + attr[2] * b[2][1], &(attr[3]));
		f(attr[0] + attr[1] * b[3][0] + attr[2] * b[3][1] + attr[3] * b[3][2], &(attr[4]));
		f(attr[0] + attr[1] * b[4][0] + attr[2] * b[4][1] + attr[3] * b[4][2] + attr[4] * b[4][3], &(attr[5]));
		f(attr[0] + attr[1] * b[5][0] + attr[2] * b[5][1] + attr[3] * b[5][2] + attr[4] * b[5][3] + attr[5] * b[5][4], &(attr[6]));
		f(attr[0] + attr[1] * b[6][0] + attr[3] * b[6][2] + attr[4] * b[6][3] + attr[5] * b[6][4] + attr[6] * b[6][5], &(attr[7]));
		for(i = 1; i <= 7; i++) attr[i] *= step_ad;
		attr[8] = attr[1] * b[7][0] + attr[3] * b[7][2] + attr[4] * b[7][3] + attr[5] * b[7][4] + attr[6] * b[7][5] + attr[7] * b[7][6];
		attr[9] = attr[1] * b[8][0] + attr[3] * b[8][2] + attr[4] * b[8][3] + attr[5] * b[8][4] + attr[6] * b[8][5] + attr[7] * b[8][6];
		err = error(attr[8] - attr[9]);
		s = pow(mistake * step/(2*1), 0.2);
		attr[0] += attr[8];
		time += step_ad;
		if (step_ad * s > step) step_ad = step;
		else if (step_ad * s < step * 0.0001) step_ad = step * 0.0001;
		
	}
	attr[0].save(atl, scale);
	
	return &attr[0];
}

Phase_space* attr_creator(Atlas* atl)
{
	int j = 0;
	Phase_space_node tmp;
	Phase_space* attr = new Phase_space[10];
	if (atl->amount == 0)
	{
		for(int i = 0; i < 10; i ++)
		{
			attr[i].amount = 0;
			while(attr[i].amount != atl-> amount)
			{
				if (attr[i].amount == 0)
				{
					attr[i].first = new Phase_space_node_el;
					attr[i].first -> body = Phase_vector();
					attr[i].first -> next = NULL;
					attr[i].first -> mass = 0;
					attr[i].first -> order = j;
					tmp = attr[i].first;
					attr[i].amount ++;
					j++;
				}
				else
				{
					tmp -> next = new Phase_space_node_el;
					tmp = tmp -> next;
					tmp -> body = Phase_vector();
					tmp -> mass = 0;
					tmp -> next = NULL;
					tmp -> order = j;
					attr[i].amount ++;
					j++;
				}
			}
		}
		return attr;
	}
	
	int i = 0;
	Atlas_node tmp2 = atl->first;
	attr[0].amount = 0;
	while(tmp2 != NULL)
	{
		if (attr[0].amount == 0)
		{
			attr[0].first = new Phase_space_node_el;
			attr[0].first -> body = Phase_vector(tmp2->body.x, tmp2->body.y, tmp2->body.v_x, tmp2->body.v_y);
			attr[0].first -> next = NULL;
			attr[0].first -> mass = tmp2->body.Mass;
			tmp = attr[0].first;
			attr[0].first -> order = i;
			tmp2 = tmp2 -> next;
			attr[0].amount++;
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
			attr[0].amount ++;
			i++;
			}
	}
	
	for(int i = 1; i < 10; i ++)
	{
		attr[i].amount = 0;
		while(attr[i].amount != atl-> amount)
		{
			if (attr[i].amount == 0)
			{
				attr[i].first = new Phase_space_node_el;
				attr[i].first -> body = Phase_vector();
				attr[i].first -> next = NULL;
				attr[i].first -> mass = 0;
				attr[i].first -> order = j;
				tmp = attr[i].first;
				attr[i].amount ++;
				j++;
			}
			else
			{
				tmp -> next = new Phase_space_node_el;
				tmp = tmp -> next;
				tmp -> body = Phase_vector();
				tmp -> mass = 0;
				tmp -> next = NULL;
				tmp -> order = j;
				attr[i].amount ++;
				j++;
			}
		}
	}
	return attr;
}

Phase_space* attr_add(Phase_space* attr, Celestial_Body* a)
{
	attr[0].add(a);
	for (int i = 1; i < 10; i ++)
	{
		attr[i].add();
	}
	return attr;
}

Phase_space* attr_remove(Phase_space* attr, Atlas* atl)
{
	for (int i = 0; i < 10; i++) attr[i].remove();
	if (attr[0].amount != atl->amount) return attr;
	if (atl -> amount == 0) return attr;
	Atlas_node tmp = atl->first;
	Phase_space_node tmp1 = attr[0].first;
	while (tmp != NULL)
	{
		tmp1->body = Phase_vector(tmp->body.x, tmp->body.y, tmp->body.v_x, tmp->body.v_y);
		tmp1->mass = tmp->body.Mass;
		tmp = tmp -> next;
		tmp1 = tmp1 -> next;
	}
	return attr;
}


