#ifndef GENERAL
#define GENERAL

#include <iostream>
#include <pthread.h>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "celestial_body.hpp"
#include "method_Dormand_Prince.hpp"
#include "method_Runga_Kutta.hpp"

#include "celestial_body.cpp"
#include "method_Dormand_Prince.cpp"
#include "method_Runga_Kutta.cpp"
#include "input_last.cpp"


using namespace sf;

int fatal_error = 0;
#endif
