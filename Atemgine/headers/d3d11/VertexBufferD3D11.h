#pragma once

#include "..\base\VertexBufferBase.h"
#include <d3d11.h>

class IDirect3D11VertexBuffer : public IVertexBufferBase
{
public:
protected:
	bool APIInitialize(VertexUploadData vertexData);
	void APIDestroy();
	void APIBind();
private:
	UINT m_stride;
	ID3D11Buffer* m_vertexBuffer;
};