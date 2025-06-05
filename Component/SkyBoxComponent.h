#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<vector>
#include<glm/gtc/matrix_transform.hpp>
#include<ShaderComponent.h>
#include<CameraComponent.h>


class SkyBox 
{
public:
    
	unsigned int _Count;
	SkyBox(vector<const char*> _Texture);
	void Draw(Shader& _Shader, Camera& _Camera);
	
private:
	void AddSkyBox(vector<const char*> _SkyTexture);
	unsigned int _VAO, _VBO, _EBO;
	
};
