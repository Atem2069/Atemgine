#pragma once

#include "..\base\RenderDeviceBase.h"
#include<d3d11.h>

class IDirect3D11RenderDevice : public IRenderDeviceBase
{
public:
	virtual void destroy();
	virtual ID3D11Device* getDevice();
	virtual ID3D11DeviceContext* getDeviceContext();
protected:
	virtual void APISetDevice(ID3D11Device* device);
	virtual void APISetDeviceContext(ID3D11DeviceContext* deviceContext);
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;

	friend class IDirect3D11Renderer;
};