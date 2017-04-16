#include <iostream> 
#include <string>
#include <fstream>
#include "celestial_body.h"
#include "celestial_body.cpp"
#include "load-save-functions.cpp"
#include <SFML/Graphics.hpp>


int main()
{
	std::string name = "Correct_save";
	Atlas atl = Atlas();
	load_system(name, &atl);
	atl.name = "Load_result";
	//save_system(atl, "Test description");
	return 0;
}
