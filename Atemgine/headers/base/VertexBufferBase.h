#pragma once

struct VertexUploadData
{
	void* rawData;
	size_t vertexSizeBytes;
	int numVertexElements;
};

class IVertexBufferBase
{
public:
	virtual bool initialize(VertexUploadData vertexData) = 0;
	virtual void destroy() = 0;

	virtual void bind() = 0;

	virtual int getVertexCount() = 0;
protected:
	int m_numVertices;
};