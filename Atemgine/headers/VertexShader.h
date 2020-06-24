#pragma once

#include "d3d11\VertexShaderD3D11.h"

class IVertexShader : public IDirect3D11VertexShader
{
public:
	virtual bool initialize(std::string shaderPath);
	virtual void destroy();
	virtual void bind();
};