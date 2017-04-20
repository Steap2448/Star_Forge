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
	save_system(atl, "Load_result");
	filename_list name_list;
	dir_preview(&name_list);
	
	
	
	filename *tmp = name_list.first;
	while(tmp != NULL)
	{
		std::cout<<tmp->name<<std::endl;
		tmp = tmp->next;
	}
	
	
	
	
	
	
	
	
	atl.del();
	return 0;
}
