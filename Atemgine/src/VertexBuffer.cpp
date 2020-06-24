#include "..\headers\VertexBuffer.h"

bool IVertexBuffer::initialize(VertexUploadData vertexData)
{
	m_numVertices = vertexData.numVertexElements;
	return APIInitialize(vertexData);
}

void IVertexBuffer::destroy()
{
	APIDestroy();
}

void IVertexBuffer::bind()
{
	APIBind();
}

int IVertexBuffer::getVertexCount()
{
	return m_numVertices;
}

