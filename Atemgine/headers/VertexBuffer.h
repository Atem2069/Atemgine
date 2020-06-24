#pragma once

#include "d3d11\VertexBufferD3D11.h"

class IVertexBuffer : public IDirect3D11VertexBuffer
{
public:
	bool initialize(float* vertices, size_t vertexSizeBytes, int numVertexElements);
	void destroy();
	void bind();

	int getVertexCount();
};