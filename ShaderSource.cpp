#include"ShaderComponent.h"

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

	GLuint _Frag = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(_Frag, 1, &_FragShader, NULL);
	glCompileShader(_Frag);

	_Count = glCreateProgram();
	glAttachShader(_Count, _Vertex);
	glAttachShader(_Count, _Frag);
};

void Shader::UseShader() 
{
	glUseProgram(_Count);
}

void Shader::DeactivateShader() 
{
	glDeleteProgram(_Count);
}

void Shader::SetMatrix4(const char* _Name, mat4 _Parameter)
{
	UseShader();
	glUniformMatrix4fv(glGetUniformLocation(_Count, _Name), 1, GL_FALSE, value_ptr(_Parameter));
}