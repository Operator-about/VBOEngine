#include<ModelComponent.h>


//ModelSource.cpp - Engine component for importing model in engine as Assimp
//If you need create own function for import model, please write this here or in ModelComponent.h for add construction 

//-------------------------------------------------//

//ModelSource.cpp - Компонент движка для импорта модели в движок как Assimp
//Если вам нужно создать собственную функцию для импорта модели, пожалуйста, напишите это здесь или в ModelComponent.h для добавления конструкций

void Model::Draw(Shader& _Shader) 
{
	for (int i = 0; i<_MeshValue.size();i++) 
	{
		_MeshValue[i].Draw(_Shader);
	}
}

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
	cout << "if you get error at import model in engine, please see this log:" << endl;
	cout << "if you not get error, please ignore this log." << endl;
	try 
	{
		for (int i = 0; i < _Mesh->mNumVertices; i++)
		{
			vec3 _Vector;
			MeshData _Data;
			cout << "Load Vertex Mesh:" << i << endl;
			_Vector.x = _Mesh->mVertices[i].x;
			_Vector.y = _Mesh->mVertices[i].y;
			_Vector.z = _Mesh->mVertices[i].z;
			_Data._Vert = _Vector;
			if (_Mesh->HasNormals())
			{
				cout << "Load Normal Mesh:" << i << endl;
				_Vector.x = _Mesh->mNormals[i].x;
				_Vector.y = _Mesh->mNormals[i].y;
				_Vector.z = _Mesh->mNormals[i].z;
				_Data._Normal = _Vector;
			}
			if (_Mesh->mTextureCoords[0])
			{
				vec2 _Vec;
				_Vec.x = _Mesh->mTextureCoords[0][i].x;
				_Vec.y = _Mesh->mTextureCoords[0][i].y;
				_Data._TexCoord = _Vec;
			}
			else 
			{
				vec2 _Vec;
				_Vec.x = 0.0f;
				_Vec.y = 0.0f;
				_Data._TexCoord = _Vec;
			}

			_DataModel.push_back(_Data);
		}

		for (int i = 0; i < _Mesh->mNumFaces; i++)
		{
			cout << "Load Index Model." << endl;
			aiFace _Face = _Mesh->mFaces[i];
			for (int j = 0; j < _Face.mNumIndices; j++)
			{
				_Index.push_back(_Face.mIndices[j]);
			}

		}
		cout << "Import model successfully done! Model index:"<< _Mesh->mNumFaces << ". Model Vertex:" << _Mesh->mNumVertices << endl;
	}
	catch (exception _E) 
	{
		throw(errno);
	}
	
	
	return Mesh(_DataModel, _Index);
}