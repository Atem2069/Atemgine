#pragma once

#include "VertexShader.h"
#include "PixelShader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

enum PrimitiveTopology		//Enums that map primitive topology to API specific stuff (i.e. D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST or GL_TRIANGLES)
{
	TOPOLOGY_TRIANGLELIST,
	TOPOLOGY_LINELIST,
	TOPOLOGY_POINTLIST
};
enum DrawType				//Switch between drawing directly from VBO or drawing with index buffer
{
	DRAWTYPE_DIRECT,	//If Direct, ignore Index Buffer parameter
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