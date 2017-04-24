#ifndef METHOD
#define METHOD

double x(double x_m, double scale);

double y(double y_m, double scale);

double x_satellite(double x, Celestial_Body* a);

double y_satellite(double y, Celestial_Body* a);

double v_x_satellite(double v_x, Celestial_Body* a);

double v_y_satellite(double v_y, Celestial_Body* a);

double distance(Celestial_Body* a, Celestial_Body* b);

Phase_vector f(Celestial_Body* a, Atlas* atl, Phase_vector* k, int kn, double step);

Phase_vector f(Celestial_Body* a, Atlas* atl);

Phase_vector k1(Celestial_Body* a, Atlas* atl);

Phase_vector k2(Celestial_Body* a, Atlas* atl, double step, Phase_vector* k1);

Phase_vector k3(Celestial_Body* a, Atlas* atl, double step, Phase_vector* k2);

Phase_vector k4(Celestial_Body* a, Atlas* atl, double step, Phase_vector* k3);

Phase_vector Movement(Celestial_Body* a, Atlas* atl, double step);

Atlas* Motion(Atlas* atl, double t_scale, double step, double scale);

void draw(Atlas* atl, sf::RenderWindow* window);

void* Movement_paral(void* argument_v);

Atlas* Motion_paral(Atlas* atl, Pthread_array* pth_adr, double t_scale, double step);

void* Motion_paral_mod(void* argument_v);

void* test(void* a);
#endif
