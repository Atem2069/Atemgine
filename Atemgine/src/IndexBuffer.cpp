#include "..\headers\IndexBuffer.h"

bool IIndexBuffer::initialize(IndexUploadData indexData)
{
	m_numIndices = indexData.numIndices;
	return APIInitialize(indexData);
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