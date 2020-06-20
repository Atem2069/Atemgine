#pragma once

#include "..\base\RenderTargetBase.h"
#include "..\Renderer.h"
#include<d3d11.h>

class IDirect3D11RenderTarget : public IRenderTargetBase
{
protected:
	virtual bool APIinitialize(int width, int height);
	virtual void APIdestroy();

	virtual void APIsetActive();
	virtual void APIclear(XMFLOAT4 color, float depth);

	ID3D11RenderTargetView* m_renderTargetView;
};