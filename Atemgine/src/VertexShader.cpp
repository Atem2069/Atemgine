#include "..\headers\VertexShader.h"

bool IVertexShader::initialize(std::string shaderPath)
{
	return APIInitialize(shaderPath);
}

void IVertexShader::destroy()
{
	APIDestroy();
}

void IVertexShader::bind()
{
	APIBind();
}