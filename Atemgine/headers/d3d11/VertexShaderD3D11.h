#pragma once

#include "..\base\ShaderBase.h"
#include<d3d11.h>
#include <d3dcompiler.h>

class IDirect3D11VertexShader : public IShaderBase
{
public:
protected:
	bool APIInitialize(std::string pathToShader);
	void APIDestroy();

	void APIBind();
private:
	bool createReflectedInputLayout(ID3D10Blob* shaderByteCode);
	ID3D11VertexShader* m_vertexShader;
	ID3D11InputLayout* m_inputLayout;	//using shader reflection to fill out input layout instead of manual meme

	friend class IDirect3D11Renderer;
};