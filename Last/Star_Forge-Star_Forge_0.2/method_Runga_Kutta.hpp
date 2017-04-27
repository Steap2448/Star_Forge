#ifndef METHOD_RUNGA_KUTTA
#define METHOD_RUNGA_KUTTA

double b_r_k [5][4] = {{0, 	   0,       0,       0}, 
					   {0.5,   0,       0,       0}, 
					   {0,     0.5,     0,       0}, 
					   {0,     0,       0,       1},
					   {1/6.0, 2.0/6.0, 2.0/6.0, 1.0/6.0}};

#endif
