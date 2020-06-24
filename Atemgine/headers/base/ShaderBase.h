#pragma once

#include<iostream>

class IShaderBase
{
public:
	virtual bool initialize(std::string shaderPath) = 0;
	virtual void destroy() = 0;
	virtual void bind() = 0;
};