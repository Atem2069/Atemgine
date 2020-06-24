#pragma once

#include "d3d11\VertexBufferD3D11.h"

class IVertexBuffer : public IDirect3D11VertexBuffer
{
public:
	bool initialize(VertexUploadData vertexData);
	void destroy();
	void bind();

	int getVertexCount();
};