#pragma once


#include "d3d11\IndexBufferD3D11.h"

class IIndexBuffer : public IDirect3D11IndexBuffer
{
public:
	bool initialize(IndexUploadData indexData);
	void destroy();
	void bind();

	int getIndexCount();
};