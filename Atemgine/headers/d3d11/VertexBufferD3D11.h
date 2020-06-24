#pragma once

#include "..\base\VertexBufferBase.h"
#include <d3d11.h>

class IDirect3D11VertexBuffer : public IVertexBufferBase
{
public:
protected:
	bool APIInitialize(float* vertices, int numVertices);
	void APIDestroy();
	void APIBind();
private:
	ID3D11Buffer* m_vertexBuffer;
};