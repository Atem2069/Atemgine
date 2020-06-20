#pragma once

#include "..\RenderDevice.h"
#include "..\Renderer.h"
#include<DirectXMath.h>
using namespace DirectX;


class IRenderTargetBase
{
public:
	virtual bool initialize(int width, int height) = 0;	//todo make option to let rendertarget be made from arbitrary texture2d
	virtual void destroy() = 0;

	virtual void setActive() = 0;
	virtual void clear(XMFLOAT4 color, float depth) = 0;
};