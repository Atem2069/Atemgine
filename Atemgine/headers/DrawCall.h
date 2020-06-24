#pragma once

#include "VertexShader.h"
#include "PixelShader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

enum PrimitiveTopology
{
	TOPOLOGY_TRIANGLELIST,
	TOPOLOGY_LINELIST,
	TOPOLOGY_POINTLIST
};
enum DrawType
{
	DRAWTYPE_DIRECT,	//If Direct, ignore Index Buffer parameter!!!
	DRAWTYPE_INDEXED	
};

struct DrawCall
{
	IVertexBuffer* vertexBuffer;
	IIndexBuffer* indexBuffer;
	IVertexShader* vertexShader;
	IPixelShader* pixelShader;

	PrimitiveTopology primitiveTopology;
	DrawType drawType;

	int baseVertex;
	int baseIndex;
};