#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <vector>
#include <stb/stb_image.h>
#include <ShaderComponent.h>
using namespace std;
using namespace glm;

//You can write or create new construction here, but! Don't destroy base construction function here. 

//---------------------------------------//

//Вы можете написать или создать новую конструкцию здесь, но! Не удаляйте здесь базовые функции конструкций.

//You can re-write this struct if you need more variable

//------------------------------//

//Вы можете переписать данную структуры если вам нужно больше переменных
struct MeshData 
{
	vec3 _Vert;
	vec3 _Normal;
	vec2 _TexCoord;
};

class Mesh
{
public:

	unsigned int _CountTexture;
	vector<MeshData> _Vertex;
	vector<unsigned int> _Index;
	Mesh(vector<MeshData> _Vert, vector<unsigned int> _Index);
	void Draw(Shader& _Shader);

private:
	unsigned int _VAO, _VBO, _EBO;
	void AddMesh();
};
