#include "..\headers\VertexBuffer.h"

bool IVertexBuffer::initialize(float* vertices, int numVertices)
{
	m_numVertices = numVertices;
	return APIInitialize(vertices, numVertices);
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

