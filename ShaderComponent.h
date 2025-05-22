#ifndef SHADER_SYSTEM_H
#define SHADER_SYSTEM_H

#include<glad/glad.h>
#include<iostream>
#include<fstream>
#include<cerrno>
#include<sstream>
#include<string>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<GLFW/glfw3.h>
using namespace std;
using namespace glm;

string GetFile(string _File);

class Shader 
{
public:
	unsigned int _Count;
	Shader(string _VertexShader, string _FragmentShader);
	void UseShader();
	void DeactivateShader();
	void SetMatrix4(const char* _Name, mat4 _Parameter);
};

#endif
