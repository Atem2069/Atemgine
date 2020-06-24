#pragma once


#include "..\base\IndexBufferBase.h"
#include <d3d11.h>

class IDirect3D11IndexBuffer : public IIndexBufferBase
{
public:
protected:
	bool APIInitialize(IndexUploadData indexData);
	void APIDestroy();
	void APIBind();
private:
	ID3D11Buffer* m_indexBuffer;
};