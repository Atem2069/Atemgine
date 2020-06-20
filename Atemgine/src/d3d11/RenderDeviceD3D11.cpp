#include "..\..\headers\d3d11\RenderDeviceD3D11.h"

void IDirect3D11RenderDevice::destroy()
{
	if (m_device)
		m_device->Release();
	if (m_deviceContext)
		m_deviceContext->Release();
}
ID3D11Device* IDirect3D11RenderDevice::getDevice()
{
	return m_device;
}
ID3D11DeviceContext* IDirect3D11RenderDevice::getDeviceContext()
{
	return m_deviceContext;
}

void IDirect3D11RenderDevice::APISetDevice(ID3D11Device* device)
{
	m_device = device;
}
void IDirect3D11RenderDevice::APISetDeviceContext(ID3D11DeviceContext* deviceContext)
{
	m_deviceContext = deviceContext;
}