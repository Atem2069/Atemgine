#pragma once


#include "d3d11\IndexBufferD3D11.h"

class IIndexBuffer : public IDirect3D11IndexBuffer
{
public:
	bool initialize(unsigned int* indices, int numIndices);
	void destroy();
	void bind();

	int getIndexCount();
};