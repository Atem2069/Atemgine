#pragma once

class IIndexBufferBase
{
public:
	virtual bool initialize(unsigned int* indices, int numIndices) = 0;
	virtual void destroy() = 0;

	virtual void bind() = 0;

	virtual int getIndexCount() = 0;
protected:
	int m_numIndices;
};