#include "..\..\headers\d3d11\RenderTargetD3D11.h"

bool IDirect3D11RenderTarget::APIInitialize(int width, int height)
{
	ID3D11Texture2D* backBufferRef;
	IRenderer::getSwapChain()->getSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBufferRef);

	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	//todo not hardcode
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	HRESULT result = IRenderer::getRenderDevice()->getDevice()->CreateRenderTargetView(backBufferRef, &rtvDesc, &m_renderTargetView);
	if (FAILED(result))
		return false;

	backBufferRef->Release();

	D3D11_TEXTURE2D_DESC depthTextureDesc = {};
	depthTextureDesc.Width = width;
	depthTextureDesc.Height = height;
	depthTextureDesc.ArraySize = 1;
	depthTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthTextureDesc.CPUAccessFlags = 0;
	depthTextureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthTextureDesc.MipLevels = 1;
	depthTextureDesc.SampleDesc.Count = 1;
	depthTextureDesc.Usage = D3D11_USAGE_DEFAULT;

	result = IRenderer::getRenderDevice()->getDevice()->CreateTexture2D(&depthTextureDesc, nullptr, &m_depthBuffer);
	if (FAILED(result))
		return false;

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

	result = IRenderer::getRenderDevice()->getDevice()->CreateDepthStencilView(m_depthBuffer, &dsvDesc, &m_depthStencilView);
	if (FAILED(result))
		return false;

	return true;
}
void IDirect3D11RenderTarget::APIDestroy()
{
	m_renderTargetView->Release();
}

void IDirect3D11RenderTarget::APISetActive()
{
	IRenderer::getRenderDevice()->getDeviceContext()->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);
}
void IDirect3D11RenderTarget::APIClear(XMFLOAT4 color, float depth)
{
	float col[4] = { color.x,color.y,color.z,color.w };
	IRenderer::getRenderDevice()->getDeviceContext()->ClearRenderTargetView(m_renderTargetView, col);
	IRenderer::getRenderDevice()->getDeviceContext()->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, depth, 0);
}