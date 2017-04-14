#ifndef PTHREAD_MOD
#define PTHREAD_MOD

#include <pthread.h>
#include "celestial_body.h"

struct arg
{
	Atlas* atlas;
	Celestial_Body* a;
	Phase_vector res;
	double step;
};

struct arg_mod
{
	Atlas* atlas;
	Atlas_node start;
	Atlas_node finish;
	double step;
	double t_scale;
	double scale;
	int amount;
};

class Pthread_array
{
	public:
	int amount;
	pthread_t* thread;
	pthread_attr_t tattr;
	arg* argument;
	int current;
	Pthread_array();
	Pthread_array(int a, Atlas* atl);
	void equip(Celestial_Body* a, double step);
	void join();
	void next();
	void del();
};

class Pthread_base
{
	public:
	int amount;
	pthread_t* thread;
	pthread_attr_t tattr;
	arg_mod* argument;
	int current;
	int a;
	Pthread_base();
	Pthread_base(int a, Atlas* atl);
	void equip(double t_scale, double step, double scale);
	void join();
	void next();
	void del();
	void launch(double t_scale, double step, double scale);
};


#endif 
