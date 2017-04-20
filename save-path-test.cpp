#include "load-save-functions.cpp"
#include <iostream> 
#include <string>
#include <fstream>
#include "celestial_body.h"
#include <SFML/Graphics.hpp>
#include "celestial_body.cpp"
#include "interface.cpp"



int main()
{
	Atlas atl;
	atl.name = "Name";
	std::string length_tmp = atl.name;
	int name_length = length_tmp.length();
	char path_tmp[10+name_length];
	int i = 0;
	for (i = 0; i < 6; i++)
	{
		path_tmp[i] = SAVES[i];
	}
	for (i = 0; i < name_length; i++)
	{
		path_tmp[i+6] = atl.name[i];
	}
	for (i = 0; i < 4; i++)
	{
		path_tmp[6 + name_length + i] = DOTTXT[i];
	}
	const char* path = path_tmp;
	std::cout <<"path: "<<path<<endl;
	
	
	return 0;
}
