#pragma once

#include "base\RendererBase.h"
#include "d3d11\RendererD3D11.h"
#include "RenderDevice.h"

#define NOMINMAX	//Winapi fucking sucks
#define GLFW_EXPOSE_NATIVE_WIN32

struct GLFWwindow;	//forward declare meme
class IRenderer;	//more forward declares for IRenderer which ISwapChain wants
class IRenderTarget;

class ISwapChain : public IDirect3D11SwapChain
{
public:
	virtual bool initialize(int width, int height, HWND hwnd);
	virtual void destroy();
	virtual void present();
};

class IRenderer : public IDirect3D11Renderer
{
public:
	virtual bool initialize(int width, int height);
	virtual void destroy();

	virtual bool shouldClose();
	virtual void setShouldClose();
	virtual void processEvents();

	virtual void present();

	virtual void draw(DrawCall drawCallInfo);

	static ISwapChain* getSwapChain();
	static IRenderDevice* getRenderDevice();
	static IRenderer* getCurrentInstance();
	IRenderTarget* getRenderTarget();
private:
	GLFWwindow* m_window;
	static ISwapChain* m_swapChain;
	static IRenderDevice* m_renderDevice;
	static IRenderer* m_currentInstance;
	IRenderTarget* m_defaultRenderTarget;
};