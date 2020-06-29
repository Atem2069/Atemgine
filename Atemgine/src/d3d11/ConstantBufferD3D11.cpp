#include "..\..\headers\d3d11\ConstantBufferD3D11.h"
#include "..\..\headers\Renderer.h"
bool IDirect3D11ConstantBuffer::APIInitialize(ConstantBufferUploadInfo bufferData)
{
	D3D11_BUFFER_DESC constBufferDesc = {};
	constBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constBufferDesc.ByteWidth = bufferData.sizeBytes;;
	constBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	constBufferDesc.MiscFlags = 0;
	constBufferDesc.StructureByteStride = 0;;
	constBufferDesc.Usage = D3D11_USAGE_DYNAMIC;

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
	void* ptr;
	D3D11_MAPPED_SUBRESOURCE mappedData = {};
	HRESULT result = IRenderer::getRenderDevice()->getDeviceContext()->Map(m_constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
	if (FAILED(result))
		return false;
	
	memcpy(mappedData.pData, bufferData.rawData, bufferData.sizeBytes);

	IRenderer::getRenderDevice()->getDeviceContext()->Unmap(m_constantBuffer, 0);
	return true;
}