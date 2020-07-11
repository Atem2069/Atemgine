#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<DirectXMath.h>
using namespace DirectX;

#include "..\Renderer.h"
#include "..\VertexBuffer.h"
#include "..\IndexBuffer.h"

struct Vertex
{
	XMFLOAT3 position;
	XMFLOAT3 normal;
};


class IModel
{
public:
	bool load(std::string path);
	void destroy();

	void writeDrawCall(DrawCall& drawCall);	//Writes model information to current draw call. intended to be used in a scene manager which generates and dispatches draw calls
		
	XMMATRIX transform;
private:
	IVertexBuffer* vertexBuffer;
	IIndexBuffer* indexBuffer;
	IConstantBuffer* transformContainer;
	std::vector<DrawInstance> meshes;	//DrawInstance struct contains most of the data we need to describe a mesh right now. 
};