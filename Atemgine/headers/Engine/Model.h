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

	void writeDrawCall(DrawCall& drawCall);
private:
	IVertexBuffer* vertexBuffer;
	IIndexBuffer* indexBuffer;
	std::vector<DrawInstance> meshes;	//DrawInstance struct contains most of the data we need to describe a mesh right now. 
};