#pragma once

#include "d3d11\ConstantBufferD3D11.h"

class IConstantBuffer : public IDirect3D11ConstantBuffer
{
public:
	virtual bool initialize(ConstantBufferUploadInfo bufferData);
	virtual void destroy();

	virtual void setBinding(ConstBufferBindingLocation bindingLocation, int binding);
	virtual void bind();

	virtual bool update(ConstantBufferUploadInfo bufferData);
private:
	ConstBufferBindingLocation m_bindingLocation;
	int m_binding;
};