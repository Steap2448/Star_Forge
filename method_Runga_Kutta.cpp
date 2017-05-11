#include "method_Runga_Kutta.hpp"



Phase_space* Motion(Atlas* atl, double t_scale, double step, double scale, Phase_space* attr, double err)////Correct exeptions
{
	double time = 0;
	if (atl-> amount == 0) 
	{
		if (atl -> amount == 1) attr[0].save(atl, scale);
		return &attr[0];
	}
	int i;
	Phase_space_node tmp1, tmp2;
	while(time < t_scale)
	{
		f(attr[0], &(attr[1]), err);
		f(attr[0] + attr[1] * b_r_k[1][0], &(attr[2]), err);
		f(attr[0] + attr[2] * b_r_k[2][1], &(attr[3]), err);
		f(attr[0] + attr[3] * b_r_k[3][2], &(attr[4]), err);
		for(i = 1; i <= 7; i++) attr[i] *= step;
		attr[8] = attr[1] * b[4][0] + attr[2] * b[4][1] + attr[3] * b[4][2] + attr[4] * b[4][3];
		attr[0] += attr[8];
		time += step;
		
	}
	attr[0].save(atl, scale);
	
	return &attr[0];
}

Phase_space* Motion(Atlas* atl, double t_scale, double step, double scale, Phase_space* attr, double err,double aph, sf::Vector2i p,double blo)////Correct exeptions
{
	double time = 0;
	if (atl-> amount == 0) 
	{
		if (atl -> amount == 1) attr[0].save(atl, scale,aph,p,blo);
		return &attr[0];
	}
	int i;
	Phase_space_node tmp1, tmp2;
	while(time < t_scale)
	{
		f(attr[0], &(attr[1]), err);
		f(attr[0] + attr[1] * b_r_k[1][0], &(attr[2]), err);
		f(attr[0] + attr[2] * b_r_k[2][1], &(attr[3]), err);
		f(attr[0] + attr[3] * b_r_k[3][2], &(attr[4]), err);
		for(i = 1; i <= 7; i++) attr[i] *= step;
		attr[8] = attr[1] * b[4][0] + attr[2] * b[4][1] + attr[3] * b[4][2] + attr[4] * b[4][3];
		attr[0] += attr[8];
		time += step;
		
	}
	attr[0].save(atl, scale ,aph, p, blo);
	
	return &attr[0];
}
