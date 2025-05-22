#include "MeshComponent.h"

Mesh::Mesh(vector<MeshData> _Vert, vector<unsigned int> _Index)
{
	this->_Vertex = _Vert;
	this->_Index = _Index;

	AddMesh();
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
}

void Mesh::Draw(Shader& _Shader) 
{
	glBindVertexArray(_VAO);

	_Shader.UseShader();

	mat4 _Model = mat4(1.0f);

	_Shader.SetMatrix4("model", _Model);

	glDrawElements(GL_TRIANGLES, _Index.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}