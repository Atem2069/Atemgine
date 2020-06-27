#pragma once

#include "d3d11\ConstantBufferD3D11.h"

class IConstantBuffer : public IDirect3D11ConstantBuffer
{
public:
	virtual bool initialize(ConstantBufferUploadInfo bufferData);
	virtual void destroy();

	virtual void bind(ConstBufferBindingLocation bindingLocation, int binding);

	virtual bool update(ConstantBufferUploadInfo bufferData);
};