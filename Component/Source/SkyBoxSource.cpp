#include<SkyBoxComponent.h>

SkyBox::SkyBox(vector<const char*> _Texture)
{
	AddSkyBox(_Texture);
}

void SkyBox::AddSkyBox(vector<const char*> _SkyTexture) 
{
	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &_VBO);

	glBindVertexArray(_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, _Vertex.size() * sizeof(float), &_Vertex[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);


	glGenTextures(1, &_Count);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _Count);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	int _Width, _Height, _Channel;
	unsigned char* _Data;
	for (int i = 0; i<_SkyTexture.size(); i++) 
	{
		_Data = stbi_load(_SkyTexture[i], &_Width, &_Height, &_Channel, 0);

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, _Width, _Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _Data);
		stbi_image_free(_Data);
	}
}

void SkyBox::Draw(Shader& _Shader, Camera& _Camera) 
{
	glDepthFunc(GL_LEQUAL);
	glBindVertexArray(_VAO);

	mat4 _View = mat4(mat3(_Camera.GetView()));

	_Shader.UseShader();
	_Shader.SetMatrix4("view", _View);
	_Shader.SetMatrix4("proj", _Camera.GetProjection());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _Count);	
	_Shader.SetInt("sky", 0);

	glDrawElements(GL_TRIANGLES, 8, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS);
}