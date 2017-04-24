#include "pthread_mod.hpp"

Pthread_array::Pthread_array()
{
	amount = 0;
	current = 0;
	argument = NULL;
	thread = NULL;
}

Pthread_array::Pthread_array(int a, Atlas* atl)
{
	amount = a;
	thread = new pthread_t;
	current = 0;
	argument = new arg;
	int i;
	for (i = 0; i < amount; i ++)
	{
		argument[i].atlas = atl;
	}	
}

void Pthread_array::join()
{
	int i;
	for (i = 0; i <= current; i ++) pthread_join(thread[i], NULL);//rewrite in future
	for (i = 0; i <= current; i ++)
	{
		*(argument[i].a) += argument[i].res; ;
	}
	current = 0;
	return;
}
	
void Pthread_array::next()
{
	if((current + 1) >= amount)
	{
		Pthread_array::join();
		current = 0;
		return;
	}
	current++;
	return;
}

void Pthread_array::equip(Celestial_Body* a, double step)
{
	argument[current].a = a;
	argument[current].step = step;
	return;
}

void Pthread_array::del()
{
	delete[] thread;
	delete[] argument;
}

//Pthread_base

void devision(arg_mod* argument, int amount)
{
	int amount_of_bodies = argument[0].atlas->amount;
	int i, sum = 0;
	for (i = 0; i < amount; i ++) 
	{
		argument[i].amount = amount_of_bodies/amount;
		sum += argument[i].amount;
	}
	i = 0;
	while (sum != amount_of_bodies)
	{
		argument[i].amount++;
		sum++;
		i++;
		if (i == amount) i = 0;
	}
	return;
}

Pthread_base::Pthread_base()
{
	amount = 0;
	current = 0;
	argument = NULL;
	thread = NULL;
}

Pthread_base::Pthread_base(int a, Atlas* atl)
{
	if (a > atl -> amount) amount = atl -> amount;
	else amount = a;
	thread = new pthread_t[amount];
	current = 0;
	argument = new arg_mod[amount];
	pthread_attr_init(&tattr);
	pthread_attr_setdetachstate(&tattr, PTHREAD_CREATE_JOINABLE);
	int i;
	for (i = 0; i < amount; i ++)
	{
		argument[i].atlas = atl;
	}
	devision(argument, amount);
	i = -1;
	int k = 0;
	Atlas_node tmp = atl->first;
	while (i != amount)
	{

		if ((k == 0))
		{
			i++;
			if ((i == amount))
			{
				argument[i - 1].finish = tmp;
				break;
			}
			if (i != 0)
			{
				argument[i - 1].finish = tmp;
				tmp = tmp -> next;
			}
			k = argument[i].amount;
			argument[i].start = tmp;
			k--;
		}
		else 
		{
			tmp = tmp -> next;
			k--;
		}
	}
		
}

/*void Pthread_base::join()
{
	int i;
	for (i = 0; i <= current; i ++) pthread_join(thread[i], NULL);//rewrite in future
	/*for (i = 0; i <= current; i ++)
	{
		//cout<<"tmp before "<<*(argument[i].a)<<"\n";
		//cout<<"tmp before speed"<<argument[i].a->v_x<<" "<<argument[i].a->v_x<<"\n";
		//*(argument[i].a) += argument[i].res; ;
		//cout<<"tmp after "<<*(argument[i].a)<<"\n";
		//cout<<"tmp after speed"<<argument[i].a->v_x<<" "<<argument[i].a->v_x<<"\n";
	}
	current = 0;
	return;
}*/
	
/*void Pthread_base::next()
{
	if((current + 1) >= amount)//consider rewriting
	{
		Pthread_array::join();
		current = 0;
		//cout<<"current "<<current<<"\n";
		return;
	}
	current++;
	//cout<<"current "<<current<<"\n";
	//cout<<"amount "<<amount<<"\n";
	return;
}*/

void Pthread_base::equip(double t_scale, double step, double scale)
{
	int i = 0;
	for (i = 0; i < amount; i ++)
	{
		argument[i].step = step;
		argument[i].t_scale = t_scale;
		argument[i].scale = scale;
	}
	return;
}

void Pthread_base::del()
{
	delete[] thread;
	delete[] argument;
}

void Pthread_base::launch(double t_scale, double step, double scale)
{
	Pthread_base::equip(t_scale, step, scale);
	int i;
	for(i = 0; i < amount; i ++) pthread_create(&(thread[i]), &tattr, Motion_paral_mod,(void*) &(argument[i]));
	for(i = 0; i < amount; i ++) pthread_join(thread[i], NULL);
	return;
}
