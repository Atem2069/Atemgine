#include "..\headers\ConstantBuffer.h"

bool IConstantBuffer::initialize(ConstantBufferUploadInfo bufferData)
{
	return APIInitialize(bufferData);
}

void IConstantBuffer::destroy()
{
	APIDestroy();
}

void IConstantBuffer::setBinding(ConstBufferBindingLocation bindingLocation, int binding)
{
	m_bindingLocation = bindingLocation;
	m_binding = binding;
}

void IConstantBuffer::bind()
{
	APIBind(m_bindingLocation, m_binding);
}

bool IConstantBuffer::update(ConstantBufferUploadInfo bufferData)
{
	return APIUpdate(bufferData);
}