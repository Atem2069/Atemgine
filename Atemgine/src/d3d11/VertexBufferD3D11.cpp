#include "..\..\headers\d3d11\VertexBufferD3D11.h"
#include "..\..\headers\Renderer.h"

bool IDirect3D11VertexBuffer::APIInitialize(float* vertices, int numVertices)
{
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.ByteWidth = numVertices * sizeof(float);
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;;
	bufferDesc.StructureByteStride = 0;;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA vertexData = {};
	vertexData.pSysMem = vertices;

	HRESULT result = IRenderer::getRenderDevice()->getDevice()->CreateBuffer(&bufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
		return false;
	return true;
}

void IDirect3D11VertexBuffer::APIDestroy()
{
	m_vertexBuffer->Release();
}

void IDirect3D11VertexBuffer::APIBind()
{
	UINT stride = 0, offset = 0;
	IRenderer::getRenderDevice()->getDeviceContext()->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
}