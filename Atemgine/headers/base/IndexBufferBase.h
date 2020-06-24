#pragma once

struct IndexUploadData
{
	void* rawData;
	int numIndices;
};

class IIndexBufferBase
{
public:
	virtual bool initialize(IndexUploadData indexData) = 0;
	virtual void destroy() = 0;

	virtual void bind() = 0;

	virtual int getIndexCount() = 0;
protected:
	int m_numIndices;
};