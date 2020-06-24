#include "..\..\headers\d3d11\IndexBufferD3D11.h"
#include "..\..\headers\Renderer.h"

bool IDirect3D11IndexBuffer::APIInitialize(unsigned int* indices, int numIndices)
{
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.ByteWidth = numIndices * sizeof(unsigned int);
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;;
	bufferDesc.StructureByteStride = 0;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA indexData = {};;
	indexData.pSysMem = indices;

	HRESULT result = IRenderer::getRenderDevice()->getDevice()->CreateBuffer(&bufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
		return false;
	return true;
}

void IDirect3D11IndexBuffer::APIDestroy()
{
	m_indexBuffer->Release();
}

void IDirect3D11IndexBuffer::APIBind()
{
	IRenderer::getRenderDevice()->getDeviceContext()->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
}