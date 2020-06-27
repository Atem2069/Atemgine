#include "..\headers\ConstantBuffer.h"

bool IConstantBuffer::initialize(ConstantBufferUploadInfo bufferData)
{
	return APIInitialize(bufferData);
}

void IConstantBuffer::destroy()
{
	APIDestroy();
}

void IConstantBuffer::bind(ConstBufferBindingLocation bindingLocation, int binding)
{
	APIBind(bindingLocation, binding);
}

bool IConstantBuffer::update(ConstantBufferUploadInfo bufferData)
{
	return APIUpdate(bufferData);
}