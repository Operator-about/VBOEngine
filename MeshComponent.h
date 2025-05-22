#include <glad/glad.h>
#include<glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <vector>
#include "ShaderComponent.h"
using namespace std;
using namespace glm;



struct MeshData 
{
	vec3 _Vert;
	vec3 _Normal;
};

class Mesh
{
public:
	vector<MeshData> _Vertex;
	vector<unsigned int> _Index;
	Mesh(vector<MeshData> _Vert, vector<unsigned int> _Index);
	void Draw(Shader& _Shader);

private:
	unsigned int _VAO, _VBO, _EBO;
	void AddMesh();
};
