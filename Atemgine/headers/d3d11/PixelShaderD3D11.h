#pragma once

#include "..\base\ShaderBase.h"
#include <d3d11.h>
#include <d3dcompiler.h>

class IDirect3D11PixelShader : public IShaderBase
{
public:
protected:
	bool APIInitialize(std::string pathToShader);;
	void APIDestroy();
	void APIBind();
private:
	ID3D11PixelShader* m_pixelShader;
	
	friend class IDirect3D11Renderer;
};