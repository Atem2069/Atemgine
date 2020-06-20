#pragma once

#include "../base/RendererBase.h"
#include "../RenderDevice.h"
#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>

class IDirect3D11SwapChain : public ISwapChainBase
{
public:
	IDXGISwapChain* getSwapChain();
protected:
	virtual bool APIInitialize(IRenderDevice* m_device, int width, int height, HWND windowHwnd);	//todo fix device param
	virtual void APIpresent();
	IDXGISwapChain* m_swapChain;
};

class IDirect3D11Renderer : public IRendererBase
{
public:
protected:
	virtual IRenderDevice* APIInitialize();
};