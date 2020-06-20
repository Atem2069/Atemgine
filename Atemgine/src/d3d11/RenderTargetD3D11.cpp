#include "..\..\headers\d3d11\RenderTargetD3D11.h"

bool IDirect3D11RenderTarget::APIinitialize(int width, int height)
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
	return true;
}
void IDirect3D11RenderTarget::APIdestroy()
{
	m_renderTargetView->Release();
}

void IDirect3D11RenderTarget::APIsetActive()
{
	IRenderer::getRenderDevice()->getDeviceContext()->OMSetRenderTargets(1, &m_renderTargetView, nullptr);
}
void IDirect3D11RenderTarget::APIclear(XMFLOAT4 color, float depth)
{
	float col[4] = { color.x,color.y,color.z,color.w };
	IRenderer::getRenderDevice()->getDeviceContext()->ClearRenderTargetView(m_renderTargetView, col);
}