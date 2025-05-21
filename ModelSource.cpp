#include"ModelComponent.h"

void Model::Load(string _Path) 
{
	Importer _Import;
	const aiScene* _Scene = _Import.ReadFile(_Path, aiProcess_Triangulate);

	Node(_Scene->mRootNode, _Scene);
}

void Model::Node(aiNode* _Node, const aiScene* _Scene)
{
	for (int i = 0; i<_Node->mNumMeshes;i++) 
	{
		const aiMesh* _Mesh = _Scene->mMeshes[_Node->mMeshes[i]];
		_MeshValue.push_back(LoadModel(_Mesh, _Scene));
	}
	for (int i = 0;i<_Node->mNumChildren;i++) 
	{
		Node(_Node->mChildren[i], _Scene);
	}
}

Mesh Model::LoadModel(const aiMesh* _Mesh, const aiScene* _Scene)
{
	vector<MeshData> _LocalData;
	vector<unsigned int> _Index;
	for (int i = 0; i<_Mesh->mNumVertices;i++) 
	{
		vec3 _Vector;
		MeshData _Data;
		_Vector.x = _Mesh->mVertices[i].x;
		_Vector.y = _Mesh->mVertices[i].y;
		_Vector.z = _Mesh->mVertices[i].z;
		_Data._Vert = _Vector;
		if (_Mesh->HasNormals()) 
		{
			_Vector.x = _Mesh->mNormals[i].x;
			_Vector.y = _Mesh->mNormals[i].y;
			_Vector.z = _Mesh->mNormals[i].z;
			_Data._Normal = _Vector;
		}

		_DataModel.push_back(_Data);
	}

	for (int i = 0; i<_Mesh->mNumFaces;i++) 
	{
		aiFace _Face = _Mesh->mFaces[i];
		for (int j = 0; j<_Face.mNumIndices;j++) 
		{
			_Index.push_back(_Face.mIndices[j]);
		}

	}

	return Mesh(_DataModel, _Index);
}