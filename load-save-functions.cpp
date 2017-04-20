#include <iostream> 
#include <string>
#include <fstream>
#include <dirent.h>
#include <SFML/Graphics.hpp>
#include "celestial_body.h"
std::string SAVES="Saves/";
std::string DOTTXT=".txt";



int save_system(Atlas atl, std::string name)
{
	atl.name = name;
	std::string path_tmp = SAVES + atl.name + DOTTXT;
	const char* path = path_tmp.c_str();
	std::ofstream fout(path);
	fout << atl.amount<<" "<<std::endl;
	Atlas_node tmp = atl.first;
	for (int i = 0; i < atl.amount; i++)
	{
		fout <<tmp->body.x <<" "<<tmp->body.y<<" "<<tmp->body.v_x<<" "<<tmp->body.v_y<<" "<<tmp->body.w_x<<" "<<tmp->body.w_y<<" "<<tmp->body.Radius<<" "<<tmp->body.Mass<<" "<<tmp->body.color.toInteger()<<" "<<tmp->body.texture_path<<" "<<tmp->body.body_name<<" "<<std::endl;
		tmp = tmp->next;	
	}
	fout.close();
	return 0;
}

void load_system(std::string file_name, Atlas* atl)
{
	std::string path_tmp = SAVES + file_name + DOTTXT;
	const char* path = path_tmp.c_str();
	std::ifstream fin(path);
	int amount_for_cycle = 0;
	fin >>amount_for_cycle;
	int i = 0;
	Celestial_Body tmp_body;
	Uint32 color_tmp;
	
	for(i = 0; i < (amount_for_cycle); i++)
	{
		fin >>tmp_body.x >>tmp_body.y >>tmp_body.v_x >>tmp_body.v_y>>tmp_body.w_x >>tmp_body.w_y >>tmp_body.Radius>>tmp_body.Mass>>color_tmp>>tmp_body.texture_path>>tmp_body.body_name;
		tmp_body.color = Color(color_tmp);//set color from Uint32 stored in the save-file
		atl->add(&tmp_body);
	}
	fin.close();
	return;
}


void dir_preview()
{
	DIR* dir_ptr = opendir("Saves");
	
	
	
	
	
	closedir(dir_ptr);
	return;
}



void dir_open()
{
	DIR* dir_ptr = opendir("Saves");
	
	
	while(1)
	{
		struct dirent* tmp = readdir(dir_ptr);
		if (tmp == NULL)
		{
			closedir(dir_ptr);
			return;
		}
		std::cout << tmp->d_name <<std::endl;
	}

}






