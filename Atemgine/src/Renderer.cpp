#include "..\headers\Renderer.h"
#include "..\headers\RenderTarget.h"

#include<GLFW/glfw3.h>
#include<GLFW/glfw3native.h>

bool ISwapChain::initialize(int width, int height, HWND hwnd)
{
	return APIInitialize(IRenderer::getRenderDevice(), width, height, hwnd);
}

void ISwapChain::destroy()
{
	//todo
}

void ISwapChain::present()
{
	APIPresent();
}

bool IRenderer::initialize(int width, int height)
{
	//Create window
	if (!glfwInit())
		return false;

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	m_window = glfwCreateWindow(width, height, "Atemgine", nullptr, nullptr);
	if (!m_window)
		return false;
	m_renderDevice = APIInitialize();
	if(!m_renderDevice)
		return false;

	m_swapChain = new ISwapChain;
	if (!m_swapChain->initialize(width, height, glfwGetWin32Window(m_window)))
		return false;

	m_defaultRenderTarget = new IRenderTarget;
	if (!m_defaultRenderTarget->initialize(width, height))
		return false;

	m_currentInstance = this;

	m_deltaTimeLast = 0; m_deltaTimeCurrent = 0;

	return true;

}

void IRenderer::destroy()
{
	m_swapChain->destroy();
	m_renderDevice->destroy();
}

bool IRenderer::shouldClose()
{
	return glfwWindowShouldClose(m_window);
}

void IRenderer::setShouldClose()
{
	glfwSetWindowShouldClose(m_window, 1);
}

void IRenderer::processEvents()
{
	glfwPollEvents();
}

void IRenderer::present()
{
	IRenderer::getSwapChain()->present();
	m_deltaTimeLast = m_deltaTimeCurrent;
	m_deltaTimeCurrent = glfwGetTime();
}

void IRenderer::draw(DrawCall drawCallInfo)
{
	APIDispatchDrawCall(drawCallInfo);
}

float IRenderer::deltaTime()
{
	return m_deltaTimeCurrent - m_deltaTimeLast;
}

ISwapChain* IRenderer::getSwapChain()
{
	return m_swapChain;
}

IRenderDevice* IRenderer::getRenderDevice()
{
	return m_renderDevice;
}

IRenderer* IRenderer::getCurrentInstance()
{
	return m_currentInstance;
}

IRenderTarget* IRenderer::getRenderTarget()
{
	return m_defaultRenderTarget;
}

IRenderDevice* IRenderer::m_renderDevice = nullptr;
ISwapChain* IRenderer::m_swapChain = nullptr;
IRenderer* IRenderer::m_currentInstance = nullptr;

