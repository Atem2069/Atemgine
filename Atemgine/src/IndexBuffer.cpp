#include "..\headers\IndexBuffer.h"

bool IIndexBuffer::initialize(unsigned int* indices, int numIndices)
{
	m_numIndices = numIndices;
	return APIInitialize(indices, numIndices);
}

void IIndexBuffer::destroy()
{
	APIDestroy();
}

void IIndexBuffer::bind()
{
	APIBind();
}

int IIndexBuffer::getIndexCount()
{
	return m_numIndices;
}