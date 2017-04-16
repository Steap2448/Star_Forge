#define G 6.67408e-11

#include "celestial_body.h"
#include "math.h"


float x(float x_m, float scale)
{
	float res = (x_m * (scale))/(6.084e11) + scale/2;
	//std::cout<<"x: "<<
	return res;
}

float y(float y_m, float scale)
{
	float res = scale/2 - (y_m * scale)/(6.084e11);
	return res;
}

float distance(Celestial_Body a, Celestial_Body b)
{
	float dist = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	return dist;
}

Phase_vector f(Celestial_Body a, Atlas atl) //Тут координатам соответствуют скорости, а скоростям ускорения 
{
	float dist;
	Atlas_node tmp = atl.first;
	Phase_vector res = Phase_vector();
	res.x = a.v_x;
	res.y = a.v_y;
	res.v_x = 0;
	res.v_y = 0;
	while (tmp != NULL)
	{
		if(a.Mass != (tmp -> body.Mass))
		{
			dist = distance(a, tmp->body);
			res.v_x = res.v_x + (G *  tmp->body.Mass * (tmp->body.x - a.x) )/(dist * dist * dist);
			res.v_y = res.v_y + (G *  tmp->body.Mass * (tmp->body.y - a.y))/(dist * dist * dist);
			std::cout<<"v_x"<<res.v_x<<"v_y"<<res.v_y<<"\n";
		}
		tmp = tmp->next;
	}	
	return res;
}

Phase_vector k1(Celestial_Body& a, Atlas& atl, float t_scale)
{
	return f(a, atl);
}

Phase_vector k2(Celestial_Body& a, Atlas& atl, float t_scale, Phase_vector& k1)
{
	return f((a + (k1 * t_scale) / 2), atl);//Второе тело неподвижно?
}

Phase_vector k3(Celestial_Body& a, Atlas& atl, float t_scale, Phase_vector& k2)
{
	return f((a + (k2 * t_scale) / 2), atl);//Второе тело неподвижно?
}

Phase_vector k4(Celestial_Body& a, Atlas& atl, float t_scale, Phase_vector& k3)
{
	return f((a + (k3 * t_scale)), atl);//Второе тело неподвижно?
}

Phase_vector Movement(Celestial_Body& a, Atlas& atl, float t_scale)
{
	Phase_vector res = Phase_vector();
	Phase_vector k12 = k1(a, atl, t_scale);
	std::cout<<"k1"<<k12;
	Phase_vector k22 = k2(a, atl, t_scale, k12);
	std::cout<<"k2"<<k22;
	Phase_vector k32 = k3(a, atl, t_scale, k22);
	std::cout<<"k3"<<k32;
	Phase_vector k42 = k4(a, atl, t_scale, k32);
	std::cout<<"k4"<<k42;
	res = (k12 + (k22 * 2) + (k32 * 2) + k42) * (t_scale / 6);
	std::cout<<"Movement"<<res;
	return res;
}

void Celestial_Body::Move(float t_scale, Phase_vector k1, Phase_vector k2, Phase_vector k3, Phase_vector k4)
{
	x = x + (k1.x + (k2.x * 2) + (k3.x* 2) + k4.x) * (t_scale / 6);
	y = y + (k1.y + (k2.y * 2) + (k3.y * 2) + k4.y) * (t_scale / 6);
	v_x = v_x + (k1.v_x + (k2.v_x * 2) + (k3.v_x * 2) + k4.v_x) * (t_scale / 6);
	v_y = v_y + (k1.v_y + (k2.v_y * 2) + (k3.v_y * 2) + k4.v_y) * (t_scale / 6);
	return;
}

Atlas Motion(Atlas atl, float t_scale, float scale)
{
	Atlas_node tmp = atl.first;
	Phase_vector mov;
	while(tmp != NULL)
	{
		mov = Movement(tmp->body, atl, t_scale);
		tmp->body = tmp->body+ mov;
		tmp->avatar.setPosition(x(tmp->body.x, scale), y(tmp->body.y, scale));
		tmp = tmp->next; 
	}
	return atl;
}

void draw(Atlas atl, RenderWindow* window)
{
	Atlas_node tmp = atl.first;
	while(tmp != NULL)
	{
		window->draw(tmp->avatar);
		tmp = tmp->next;
	}	
	return;
}

