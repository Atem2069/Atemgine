#pragma once


class IVertexBufferBase
{
public:
	virtual bool initialize(float* vertices, size_t vertexSizeBytes, int numVertexElements) = 0;
	virtual void destroy() = 0;

	virtual void bind() = 0;

	virtual int getVertexCount() = 0;
protected:
	int m_numVertices;
};