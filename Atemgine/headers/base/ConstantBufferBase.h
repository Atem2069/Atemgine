#pragma once

struct ConstantBufferUploadInfo
{
	void* rawData;
	size_t offsetBytes;	//ignored for initialization, used for partial updates
	size_t sizeBytes;
};

enum ConstBufferBindingLocation	//move this into shader resource common header?
{
	BIND_VS,
	BIND_PS
};

class IConstantBufferBase
{
public:
	virtual bool initialize(ConstantBufferUploadInfo bufferData) = 0;
	virtual void destroy() = 0;

	virtual void setBinding(ConstBufferBindingLocation bindingLocation, int binding) = 0;

	virtual void bind() = 0;

	virtual bool update(ConstantBufferUploadInfo bufferData) = 0;
};