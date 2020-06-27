#include "..\..\headers\d3d11\ConstantBufferD3D11.h"
#include "..\..\headers\Renderer.h"
bool IDirect3D11ConstantBuffer::APIInitialize(ConstantBufferUploadInfo bufferData)
{
	D3D11_BUFFER_DESC constBufferDesc = {};
	constBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constBufferDesc.ByteWidth = bufferData.sizeBytes;;
	constBufferDesc.CPUAccessFlags = 0;
	constBufferDesc.MiscFlags = 0;
	constBufferDesc.StructureByteStride = 0;;
	constBufferDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA constSubData = {};
	constSubData.pSysMem = bufferData.rawData;

	HRESULT result = IRenderer::getRenderDevice()->getDevice()->CreateBuffer(&constBufferDesc, &constSubData, &m_constantBuffer);
	if (FAILED(result))
		return false;	//todo check const buffer size and automatically align to 16 bytes otherwise this always fails

	return true;
}

void IDirect3D11ConstantBuffer::APIDestroy()
{
	m_constantBuffer->Release();
}

void IDirect3D11ConstantBuffer::APIBind(ConstBufferBindingLocation bindingLocation, int binding)	//could remove and put in drawcall to allow for batched binds
{
	if (bindingLocation == BIND_VS)
		IRenderer::getRenderDevice()->getDeviceContext()->VSSetConstantBuffers(binding, 1, &m_constantBuffer);
	else if (bindingLocation == BIND_PS)
		IRenderer::getRenderDevice()->getDeviceContext()->PSSetConstantBuffers(binding, 1, &m_constantBuffer);
}

bool IDirect3D11ConstantBuffer::APIUpdate(ConstantBufferUploadInfo bufferData)
{
	//todo implement
	return false;
}