#pragma once

#include "d3d11\RenderTargetD3D11.h"

class IRenderTarget : public IDirect3D11RenderTarget
{
public:
	virtual bool initialize(int width, int height);	//todo make option to let rendertarget be made from arbitrary texture2d
	virtual void destroy();

	virtual void setActive();
	virtual void clear(XMFLOAT4 color, float depth);
};