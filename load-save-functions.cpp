#include <iostream> 
#include <string>
#include <fstream>
#include <dirent.h>
#include <SFML/Graphics.hpp>
#include "celestial_body.h"
std::string SAVES="Saves/";
std::string DOTTXT=".txt";


typedef struct _filename
{
	std::string name;
	_filename *next;
} filename;


class filename_list
{
	public:
	filename *first;
	filename *last;
	filename_list()
	{
		first = NULL;
		last = NULL;
	}
	void add(std::string str)
	{
		filename *tmp = new filename;
		tmp->next = NULL;
		tmp->name = str;
		
		
		if(last != NULL)
		{
			last->next = tmp;
			last = last -> next;
		}
		else
		{
			last = tmp;
			first = tmp;
		}
	}
	
};


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


void dir_preview(filename_list *list_ptr)
{
	DIR* dir_ptr = opendir("Saves");
	
	int i = 0;
	for(i = 0; i < 2; i++)
	{
		struct dirent* tmp = readdir(dir_ptr);
	}
	while(1)
	{
		struct dirent* tmp = readdir(dir_ptr);
		if (tmp == NULL)
		{
			closedir(dir_ptr);
			return;
		}
		
		std::string file_name = tmp->d_name;
		file_name = file_name.substr(0, file_name.find("."));         //убирание окончания .txt
		//std::cout << "file_name = "<<file_name <<std::endl;
		
		//std::cout << tmp->d_name <<std::endl;
		list_ptr->add(file_name);
		
		
	}
	
	
	
	closedir(dir_ptr);
	return;
}
