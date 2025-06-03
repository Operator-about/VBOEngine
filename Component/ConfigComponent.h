#ifndef CONFIG_H
#define CONFIG_H

#include<iostream>
#include<fstream>
#include<cerrno>
#include<sstream>
#include<string>
using namespace std;



class Config
{
public:
	Config();
	void CreateConfigFile(string _Path);
	void WriteInConfigFile(string _ConfigFile, string _Value);
	string GetConfigFile(string _ConfigFile);
	bool CheckConfigFile(string _ConfigFile);
};


#endif

