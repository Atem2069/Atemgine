#include "..\headers\PixelShader.h"

bool IPixelShader::initialize(std::string shaderPath)
{
	return APIInitialize(shaderPath);
}

void IPixelShader::destroy()
{
	APIDestroy();
}

void IPixelShader::bind()
{
	APIBind();
}