#include<ConfigComponent.h>

Config::Config() 
{

}

void Config::CreateConfigFile(string _Path) 
{
	ofstream _Config(_Path);
	cout << "File create in:" << _Path << endl;
	_Config.close();
}

void Config::WriteInConfigFile(string _ConfigFile, string _Value) 
{
	ofstream _Config(_ConfigFile);
	if (_Config.is_open()) 
	{
		_Config << _Value << endl;
		_Config.close();
	}
	else 
	{
		cout << "Error open file." << endl;
	}
	_Config.close();
}

string Config::GetConfigFile(string _ConfigFile) 
{
	string _Content;
	ifstream _In(_ConfigFile);
	if (_In.is_open()) 
	{
		string _ConfigContent;
		while (getline(_In, _ConfigContent)) 
		{
			_Content = _ConfigContent;
		}
	}
	_In.close();
	return _Content;
	
}

bool Config::CheckConfigFile(string _ConfigFile) 
{
	ofstream _Config(_ConfigFile);
	if (_Config.is_open()) 
	{
		cout << "This file valid!" << endl;
		return true;
	}
	else 
	{
		cout << "This file not found, create config file." << endl;
		CreateConfigFile(_ConfigFile);
		return false;
	}
}