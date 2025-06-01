#include<ShaderComponent.h>

//ShaderSource.cpp - Engine component for attach and compiler shader for VBOEngine
//Strongly recommend: not to change or add anything here or in ShaderComponent.h
//Strongly recommend: create new shader only in type file format: .glsl
//But, if you need create own function for shader, please write this here or in ShaderComponent.h for add construction 

//---------------------------------------------------//

//ShaderSource.cpp - компонент движка для присоединения и компиляции шейдеров для VBOEngine
//Настоятельно рекомендую: не менять и не добавлять ничего здесь или в ShaderComponent.h
//Настоятельно рекомендую: создавать новые шейдеры только в формате файла типа: .glsl
//Но если вам нужно создать собственную функцию, пожалуйста, напишите это здесь или в ShaderComponent.h для добавления конструкций

string GetFile(string _File)
{
	ifstream _In(_File, ios::binary);
	if (_In)
	{
		string _Contents;
		_In.seekg(0, ios::end);
		_Contents.resize(_In.tellg());
		_In.seekg(0, ios::beg);
		_In.read(&_Contents[0], _Contents.size());
		_In.close();
		return(_Contents);
	}
	throw(errno);
};

Shader::Shader(string _VertexShader, string _FragmentShader)
{
	string _VertCode = GetFile(_VertexShader);
	string _FragCode = GetFile(_FragmentShader);

	const char* _VertShader = _VertCode.c_str();
	const char* _FragShader = _FragCode.c_str();

	GLuint _Vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(_Vertex, 1, &_VertShader, NULL);
	glCompileShader(_Vertex);
	ErrorCheckInShader("Shader");

	GLuint _Frag = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(_Frag, 1, &_FragShader, NULL);
	glCompileShader(_Frag);
	ErrorCheckInShader("Shader");

	_Count = glCreateProgram();
	glAttachShader(_Count, _Vertex);
	glAttachShader(_Count, _Frag);
	glLinkProgram(_Count);
	ErrorCheckInShader("Program");
};

void Shader::UseShader() 
{
	glUseProgram(_Count);
}

void Shader::DeactivateShader() 
{
	glDeleteProgram(_Count);
}

void Shader::SetMatrix4(const char* _Name, const mat4 _Parameter) const
{
	glUniformMatrix4fv(glGetUniformLocation(_Count, _Name), 1, GL_FALSE, value_ptr(_Parameter));
}

void Shader::SetVector3(const char* _Name, vec3 _Parameter) const 
{
	glUniform3fv(glGetUniformLocation(_Count, _Name), 1, value_ptr(_Parameter));
}

void Shader::SetInt(const char* _Name, int _Parameter) const 
{
	glUniform1i(glGetUniformLocation(_Count, _Name), _Parameter);
}

void Shader::SetBool(const char* _Name, bool _Parameter) const 
{
	glUniform1i(glGetUniformLocation(_Count, _Name), (int)_Parameter);
}

void Shader::ErrorCheckInShader(string _Type) 
{
	GLint _Succes;
	GLchar _Log[1024];
	if (_Type=="Shader")
	{
		glGetShaderiv(_Count, GL_COMPILE_STATUS, &_Succes);
		if (!_Succes)
		{
			glGetShaderInfoLog(_Count, 1024, NULL, _Log);
			cout << "Shader error:" << _Log << endl;
		}
		else
		{
			cout << "Shader not have error!" << endl;
		}
	}

	if (_Type == "Program")
	{
		glGetProgramiv(_Count, GL_LINK_STATUS, &_Succes);
		if (!_Succes)
		{
			glGetProgramInfoLog(_Count, 1024, NULL, _Log);
			cout << "Program link error:" << _Log << endl;
		}
		else
		{
			cout << "Program link status: success" << endl;
		}
	}
}