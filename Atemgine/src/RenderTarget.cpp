#include "..\headers\RenderTarget.h"

bool IRenderTarget::initialize(int width, int height)
{
	return APIInitialize(width, height);
}

void IRenderTarget::destroy()
{
	APIDestroy();
}

void IRenderTarget::setActive()
{
	APISetActive();
}

void IRenderTarget::clear(XMFLOAT4 color, float depth)
{
	APIClear(color, depth);
}