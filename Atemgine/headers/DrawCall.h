#pragma once

#include "VertexShader.h"
#include "PixelShader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"

#include<vector>

class ITexture2D;

enum PrimitiveTopology		//Enums that map primitive topology to API specific stuff (i.e. D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST or GL_TRIANGLES)
{
	TOPOLOGY_TRIANGLELIST,
	TOPOLOGY_LINELIST,
	TOPOLOGY_POINTLIST
};
enum DrawType				//Switch between drawing directly from VBO or drawing with index buffer
{
	DRAWTYPE_DIRECT,	//If Direct, ignore Index Buffer parameter
	DRAWTYPE_INDEXED,
	DRAWTYPE_MULTIDRAWINDEXED
};

struct DrawInstance
{
	int numIndices;
	int baseVertex;
	int baseIndex;
	int textureID;
};

struct DrawCall
{
	IVertexBuffer* vertexBuffer;
	IIndexBuffer* indexBuffer;
	IVertexShader* vertexShader;
	IPixelShader* pixelShader;

	//IConstantBuffer** constantBuffers;
	//int numConstantBuffers;
	std::vector<IConstantBuffer*> constantBuffers;
	//shader resource stuff here

	PrimitiveTopology primitiveTopology;
	DrawType drawType;

	std::vector<DrawInstance> drawInstances;
};

