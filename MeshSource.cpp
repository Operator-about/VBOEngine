#include "MeshComponent.h"

//MeshSource.cpp - Engine component for mesh
//If you need create own function for mesh, please write this here or in MeshComponent.h for add construction 

//----------------------------------------//

//MeshSource.cpp - Компонент движка для меша
//Если вам нужно создать собственную функцию для меша, пожалуйста, напишите это здесь или в MeshComponent.h для добавления конструкций

Mesh::Mesh(vector<MeshData> _Vert, vector<unsigned int> _Index)
{
	this->_Vertex = _Vert;
	this->_Index = _Index;

	AddMesh();
}



void Mesh::Draw(Shader& _Shader)
{
	glBindVertexArray(_VAO);

	_Shader.UseShader();

	mat4 _Model = mat4(1.0f);
	_Model = translate(_Model, vec3(0.0f, 0.0f, 0.0f));
	_Model = scale(_Model, vec3(1.0f, 1.0f, 1.0f));
	vec3 _Color = vec3(1.0f, 1.0f, 1.0f);

	_Shader.SetMatrix4("model", _Model);
	_Shader.SetVector3("Color", _Color);

	//This call set: use texture or color for model
	//You can switch bool parameter: true or false
	_Shader.SetBool("TextureValid", false);

	_Shader.SetInt("Texture", 0);

	glActiveTexture(GL_TEXTURE0);
	glDrawElements(GL_TRIANGLES, _Index.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::AddMesh() 
{
	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &_VBO);
	glGenBuffers(1, &_EBO);

	glBindVertexArray(_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, _Vertex.size() * sizeof(MeshData), &_Vertex[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _Index.size() * sizeof(unsigned int), &_Index[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(MeshData), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(MeshData), (void*)offsetof(MeshData, _Normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(MeshData), (void*)offsetof(MeshData, _TexCoord));

	
	//Texture load
	int _Width, _Height, _Channel;
	unsigned char* _Data = stbi_load("You're texture|.png|.jpg", &_Width, &_Height, &_Channel, 0);

	glGenTextures(1, &_CountTexture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _CountTexture);

	glTextureParameteri(_CountTexture, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(_CountTexture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTextureParameteri(_CountTexture, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(_CountTexture, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _Width, _Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _Data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(_Data);
	
	
	
}

