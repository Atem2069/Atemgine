#pragma once

#include "../base/RendererBase.h"
#include "../RenderDevice.h"
#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>

class IDirect3D11SwapChain : public ISwapChainBase
{
public:
protected:
	virtual bool APIInitialize(IRenderDevice* m_device, int width, int height, HWND windowHwnd);	//todo fix device param
	virtual void APIPresent();
	IDXGISwapChain* getSwapChain();
	IDXGISwapChain* m_swapChain;
	friend class IDirect3D11Renderer;
	friend class IDirect3D11RenderTarget;
};

class IDirect3D11Renderer : public IRendererBase
{
public:
protected:
	virtual IRenderDevice* APIInitialize();
	virtual void APIDispatchDrawCall(DrawCall drawCall);
private:
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
};