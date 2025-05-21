#include<assimp/scene.h>
#include<assimp/postprocess.h>
#include<assimp/Importer.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<string>
#include<vector>
#include"MeshComponent.h"
using namespace std;
using namespace Assimp;


class Model 
{
public:
	Model(string _Path)
	{
		Load(_Path);
	};
	void Draw();
private:

	vector<Mesh> _MeshValue;
	vector<MeshData> _DataModel;

	void Load(string _Path);
	void Node(aiNode* _Node, const aiScene* _Scene);
	Mesh LoadModel(const aiMesh* _Mesh, const aiScene* _Scene);
};


