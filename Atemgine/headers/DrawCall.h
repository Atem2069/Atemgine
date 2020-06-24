#pragma once

#include "VertexShader.h"
#include "PixelShader.h"

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

class IVertexBuffer;
class IIndexBuffer;
//class IVertexShader;
//class IPixelShader;	//forward declare classes that go into drawcall

struct DrawCall
{
	IVertexBuffer* vertexBuffer;
	IIndexBuffer* indexBuffer;
	IVertexShader* vertexShader;
	IPixelShader* pixelShader;

	PrimitiveTopology primitiveTopology;
	DrawType drawType;
};