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
	return true;
}

void IDirect3D11SwapChain::APIpresent()
{
	m_swapChain->Present(0, 0);
}

//D3D Device

IRenderDevice* IDirect3D11Renderer::APIInitialize()
{
	IRenderDevice* renderDevice = new IRenderDevice;
	ID3D11Device* tempDevice;
	ID3D11DeviceContext* tempDeviceContext;
	HRESULT result;
	D3D_FEATURE_LEVEL featureLevels[1] = { D3D_FEATURE_LEVEL_11_0 };
	result = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, D3D11_CREATE_DEVICE_DEBUG, featureLevels, 1, D3D11_SDK_VERSION, &tempDevice, nullptr, &tempDeviceContext);
	if (FAILED(result))
		return nullptr;
	renderDevice->APISetDevice(tempDevice);
	renderDevice->APISetDeviceContext(tempDeviceContext);
	return renderDevice;
}