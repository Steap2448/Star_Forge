#include <iostream> 
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "celestial_body.h"
using namespace std;
string SAVES="Saves/";
string DOTTXT=".txt";



int save_system(Atlas atl, const char* desc)
{
	string path_tmp = SAVES + atl.name + DOTTXT;
	const char* path = path_tmp.c_str();
	ofstream fout(path);
	fout << atl.amount <<endl;
	Atlas_node tmp = atl.first;
	for (int i = 0; i < atl.amount; i++)
	{
		fout <<tmp->body.x <<" "<<tmp->body.y<<" "<<tmp->body.v_x<<" "<<tmp->body.v_y<<" "<<tmp->body.w_x<<" "<<tmp->body.w_y<<" "<<tmp->body.Radius<<" "<<tmp->body.Mass<<" "<<tmp->body.color.r<<" "<<tmp->body.color.g<<" "<<tmp->body.color.b<<" "<<tmp->body.texture_path<<" "<<endl;//
		tmp = tmp->next;
		
	}
		
	fout.close();
	return 0;
}

void load_system(std::string file_name, Atlas* atl)
{
	string path_tmp = SAVES + file_name + DOTTXT;
	const char* path = path_tmp.c_str();
	
	ifstream fin(path);
	
	int amount_tmp = 0;
	fin >>atl->amount;
	cout<<"atl.amount after reading from file: "<<atl->amount<<endl;
	int i = 0;
	float x;
	float y;
	float v_x;
	float v_y;
	float w_x;
	float w_y;
	float Radius;
	float Mass;
	
	for(i = 0; i < atl->amount; i++)
	{
		
		
	}
	
	
	
	
	fin.close();
	return;
}

int load_dir(const char* dir_name);
