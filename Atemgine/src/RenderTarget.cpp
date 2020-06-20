#include "..\headers\RenderTarget.h"

bool IRenderTarget::initialize(int width, int height)
{
	return APIinitialize(width, height);
}

void IRenderTarget::destroy()
{
	APIdestroy();
}

void IRenderTarget::setActive()
{
	APIsetActive();
}

void IRenderTarget::clear(XMFLOAT4 color, float depth)
{
	APIclear(color, depth);
}