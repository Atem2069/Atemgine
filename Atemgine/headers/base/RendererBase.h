#pragma once

#include<Windows.h>
#include "..\DrawCall.h"

class IRendererBase
{
public:
	virtual bool initialize(int width, int height) = 0;
	virtual void destroy() = 0;

	virtual bool shouldClose() = 0;
	virtual void setShouldClose() = 0;
	virtual void processEvents() = 0;

	virtual void present() = 0;

	virtual void draw(DrawCall drawCallInfo) = 0;
protected:
};

class ISwapChainBase
{
public:
	//virtual bool initialize(IRendererBase* renderer, int width, int height, HWND hwnd) = 0;
	virtual void destroy() = 0;
	virtual void present() = 0;
protected:
};