#pragma once

#include "d3d11\PixelShaderD3D11.h"

class IPixelShader : public IDirect3D11PixelShader
{
public:
	virtual bool initialize(std::string shaderPath);
	virtual void destroy();
	virtual void bind();
};