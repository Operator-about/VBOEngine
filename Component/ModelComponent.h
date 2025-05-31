#include<assimp/scene.h>
#include<assimp/postprocess.h>
#include<assimp/Importer.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<string>
#include<vector>
#include<MeshComponent.h>
#include<ShaderComponent.h>
using namespace std;
using namespace Assimp;

//You can write or create new construction here, but! Don't destroy base construction function here. 

//---------------------------------------//

//Вы можете написать или создать новую конструкцию здесь, но! Не удаляйте здесь базовые функции конструкций.

class Model 
{
public:
	Model(string _Path)
	{
		Load(_Path);
	};
	void Draw(Shader& _Shader);
private:

	//_MeshValue - This list model
	vector<Mesh> _MeshValue;

	//_DataModel - This list for data model
	vector<MeshData> _DataModel;

	void Load(string _Path);
	void Node(aiNode* _Node, const aiScene* _Scene);
	Mesh LoadModel(const aiMesh* _Mesh, const aiScene* _Scene);
};


