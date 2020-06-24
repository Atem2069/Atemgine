#pragma once

#include "..\base\RenderTargetBase.h"
#include "..\Renderer.h"
#include<d3d11.h>

class IDirect3D11RenderTarget : public IRenderTargetBase
{
protected:
	virtual bool APIInitialize(int width, int height);
	virtual void APIDestroy();

	virtual void APISetActive();
	virtual void APIClear(XMFLOAT4 color, float depth);

	ID3D11RenderTargetView* m_renderTargetView;

	ID3D11Texture2D* m_depthBuffer;
	ID3D11DepthStencilView* m_depthStencilView;

	friend class IDirect3D11Renderer;
};