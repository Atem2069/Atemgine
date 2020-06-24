#include "../../headers/d3d11/RendererD3D11.h"

//Swapchain

IDXGISwapChain* IDirect3D11SwapChain::getSwapChain()
{
	return m_swapChain;
}

bool IDirect3D11SwapChain::APIInitialize(IRenderDevice* m_device, int width, int height, HWND windowHwnd)
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.BufferCount = 2;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 0;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_CENTERED;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = windowHwnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.Windowed = TRUE;	//todo fix
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	IDXGIFactory* tempFactory;
	CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&tempFactory);
	HRESULT result = tempFactory->CreateSwapChain(m_device->getDevice(), &swapChainDesc, &m_swapChain);
	if (FAILED(result))
		return false;

	tempFactory->Release();

	//set viewport
	D3D11_VIEWPORT defaultViewport = {};
	defaultViewport.MinDepth = 0;
	defaultViewport.MaxDepth = 1;
	defaultViewport.Width = width;
	defaultViewport.Height = height;
	m_device->getDeviceContext()->RSSetViewports(1, &defaultViewport);
	return true;
}

void IDirect3D11SwapChain::APIPresent()
{
	m_swapChain->Present(0, 0);
}

//D3D Device

IRenderDevice* IDirect3D11Renderer::APIInitialize()
{
	IRenderDevice* renderDevice = new IRenderDevice;
	HRESULT result;
	D3D_FEATURE_LEVEL featureLevels[1] = { D3D_FEATURE_LEVEL_11_0 };
	result = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, D3D11_CREATE_DEVICE_DEBUG, featureLevels, 1, D3D11_SDK_VERSION, &m_device, nullptr, &m_deviceContext);
	if (FAILED(result))
		return nullptr;
	renderDevice->APISetDevice(m_device);
	renderDevice->APISetDeviceContext(m_deviceContext);
	return renderDevice;
}

void IDirect3D11Renderer::APIDispatchDrawCall(DrawCall drawCall)
{

	drawCall.vertexShader->bind();
	drawCall.pixelShader->bind();

	switch (drawCall.primitiveTopology)	//translate shape type from front end to API specific 
	{
	case TOPOLOGY_TRIANGLELIST:
		m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		break;
	case TOPOLOGY_LINELIST:
		m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
		break;
	case TOPOLOGY_POINTLIST:
		m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);;
		break;
	}

	if (drawCall.drawType == DRAWTYPE_DIRECT)
	{
		drawCall.vertexBuffer->bind();
		m_deviceContext->Draw(drawCall.vertexBuffer->getVertexCount(), 0);
	}

	else if(drawCall.drawType = DRAWTYPE_INDEXED)
	{
		drawCall.vertexBuffer->bind();
		drawCall.indexBuffer->bind();
		m_deviceContext->DrawIndexed(drawCall.indexBuffer->getIndexCount(), 0, 0);
	}
}