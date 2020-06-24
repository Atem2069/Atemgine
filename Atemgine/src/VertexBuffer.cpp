#include "..\headers\VertexBuffer.h"

bool IVertexBuffer::initialize(float* vertices, size_t vertexSizeBytes, int numVertexElements)
{
	m_numVertices = numVertexElements;
	return APIInitialize(vertices, vertexSizeBytes, numVertexElements);
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

