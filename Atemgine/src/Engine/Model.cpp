#include "..\..\headers\Engine\Model.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

bool IModel::load(std::string path)
{
	Assimp::Importer m_importer;
	const aiScene* m_scene = m_importer.ReadFile(path, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded | aiProcess_OptimizeMeshes | aiProcess_OptimizeGraph | aiProcess_CalcTangentSpace | aiProcess_ImproveCacheLocality | aiProcessPreset_TargetRealtime_Fast);	//Convert to left handed cause d3d coordinates are special
	if (!m_scene || m_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !m_scene->mRootNode)
	{
		std::cout << "Failed to load model.. " << m_importer.GetErrorString() << std::endl;
		return false;
	}

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	int vertexBase = 0, indexBase = 0;
	for (int i = 0; i < m_scene->mNumMeshes; i++)
	{
		aiMesh* currentMesh = m_scene->mMeshes[i];
		DrawInstance currentMeshDrawInfo = {};

		for (int j = 0; j < currentMesh->mNumVertices; j++)
		{
			Vertex tempVertex = {};
			tempVertex.position.x = currentMesh->mVertices[j].x;
			tempVertex.position.y = currentMesh->mVertices[j].y;
			tempVertex.position.z = currentMesh->mVertices[j].z;

			tempVertex.normal.x = currentMesh->mNormals[j].x;
			tempVertex.normal.y = currentMesh->mNormals[j].y;
			tempVertex.normal.z = currentMesh->mNormals[j].z;

			vertices.push_back(tempVertex);
		}
		//Process indices
		int noIndices = 0;
		for (unsigned int j = 0; j < currentMesh->mNumFaces; j++)
		{
			aiFace face = currentMesh->mFaces[j];	//not recommended method at all
			for (unsigned int k = 0; k < face.mNumIndices; k++)
				indices.push_back(face.mIndices[k]);
			noIndices += face.mNumIndices;
		}

		currentMeshDrawInfo.baseVertex = vertexBase;
		vertexBase += currentMesh->mNumVertices;

		currentMeshDrawInfo.baseIndex = indexBase;
		indexBase += noIndices;

		currentMeshDrawInfo.numIndices = noIndices;

		meshes.push_back(currentMeshDrawInfo);

	}

	//Create vertex/index buffer
	VertexUploadData vboData = {};
	vboData.rawData = &vertices[0];
	vboData.vertexSizeBytes = sizeof(Vertex);
	vboData.numVertexElements = vertices.size();

	vertexBuffer = new IVertexBuffer;
	if (!vertexBuffer->initialize(vboData))
		return false;

	IndexUploadData iboData = {};
	iboData.rawData = &indices[0];
	iboData.numIndices = indices.size();
	
	indexBuffer = new IIndexBuffer;
	if (!indexBuffer->initialize(iboData))
		return false;

	return true;
}

void IModel::destroy()
{
	vertexBuffer->destroy();
	indexBuffer->destroy();
}

void IModel::writeDrawCall(DrawCall& drawCall)
{
	drawCall.vertexBuffer = vertexBuffer;
	drawCall.indexBuffer = indexBuffer;
	drawCall.drawInstances = meshes;
}