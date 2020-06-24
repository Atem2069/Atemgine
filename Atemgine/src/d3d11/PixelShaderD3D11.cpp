#include "..\..\headers\d3d11\PixelShaderD3D11.h"
#include "..\..\headers\Renderer.h"

bool IDirect3D11PixelShader::APIInitialize(std::string pathToShader)
{
	ID3D10Blob* shaderCode, *error;
	HRESULT result;
	std::wstring temp = std::wstring(pathToShader.begin(), pathToShader.end());
	LPCWSTR filePath = temp.c_str();	//d3dcompiler uses wide chars

	result = D3DCompileFromFile(filePath, nullptr, nullptr, "main", "ps_5_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &shaderCode, &error);
	if (FAILED(result))
	{
		//assuming console is open
		OutputDebugStringA((LPCSTR)error->GetBufferPointer());
		return false;
	}

	result = IRenderer::getRenderDevice()->getDevice()->CreatePixelShader(shaderCode->GetBufferPointer(), shaderCode->GetBufferSize(), nullptr, &m_pixelShader);
	if (FAILED(result))
		return false;
}

void IDirect3D11PixelShader::APIDestroy()
{
	m_pixelShader->Release();
}

void IDirect3D11PixelShader::APIBind()
{
	IRenderer::getRenderDevice()->getDeviceContext()->PSSetShader(m_pixelShader, nullptr, 0);
}