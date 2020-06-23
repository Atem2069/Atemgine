#include "..\..\headers\d3d11\VertexShaderD3D11.h"
#include "..\..\headers\Renderer.h"
#include<vector>

bool IDirect3D11VertexShader::APIInitialize(std::string pathToShader)
{
	ID3D10Blob* shaderCode, *error;
	HRESULT result;
	std::wstring temp = std::wstring(pathToShader.begin(), pathToShader.end());
	LPCWSTR filePath = temp.c_str();	//d3dcompiler uses wide chars

	result = D3DCompileFromFile(filePath, nullptr, nullptr, "main", "vs_5_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &shaderCode, &error);
	if (FAILED(result))
	{
		//assuming console is open
		OutputDebugStringA((LPCSTR)error->GetBufferPointer());
		return false;
	}

	result = IRenderer::getRenderDevice()->getDevice()->CreateVertexShader(shaderCode->GetBufferPointer(), shaderCode->GetBufferSize(), nullptr, &m_vertexShader);
	if (FAILED(result))
		return false;

	//shader reflection to get input layout
	if (!this->createReflectedInputLayout(shaderCode))
		return false;

	return true;
}

bool IDirect3D11VertexShader::createReflectedInputLayout(ID3D10Blob* shaderByteCode)
{
	// Reflect shader info
	ID3D11ShaderReflection* pVertexShaderReflection = NULL;
	if (FAILED(D3DReflect(shaderByteCode->GetBufferPointer(), shaderByteCode->GetBufferSize(), __uuidof(ID3D11ShaderReflection), (void**)&pVertexShaderReflection)))
	{
		return false;
	}

	// Get shader info
	D3D11_SHADER_DESC shaderDesc;
	pVertexShaderReflection->GetDesc(&shaderDesc);

	// Read input layout description from shader info
	std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;
	for (int i = 0; i < shaderDesc.InputParameters; i++)
	{
		D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
		pVertexShaderReflection->GetInputParameterDesc(i, &paramDesc);

			// fill out input element desc
		D3D11_INPUT_ELEMENT_DESC elementDesc;
		elementDesc.SemanticName = paramDesc.SemanticName;
		elementDesc.SemanticIndex = paramDesc.SemanticIndex;
		elementDesc.InputSlot = 0;
		elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		elementDesc.InstanceDataStepRate = 0;

			// determine DXGI format
		if (paramDesc.Mask == 1)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
		}
		else if (paramDesc.Mask <= 3)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
		}
		else if (paramDesc.Mask <= 7)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
		}
		else if (paramDesc.Mask <= 15)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		}

		//save element desc
		inputLayoutDesc.push_back(elementDesc);
	}

	// Try to create Input Layout
	HRESULT hr = IRenderer::getRenderDevice()->getDevice()->CreateInputLayout(&inputLayoutDesc[0], inputLayoutDesc.size(), shaderByteCode->GetBufferPointer(), shaderByteCode->GetBufferSize(), &m_inputLayout);
	if (FAILED(hr))
		return false;;
	//Free allocation shader reflection memory
	pVertexShaderReflection->Release();
	return true;
}

void IDirect3D11VertexShader::APIDestroy()
{
	m_vertexShader->Release();
	m_inputLayout->Release();
}

void IDirect3D11VertexShader::APIBind()
{
	IRenderer::getRenderDevice()->getDeviceContext()->VSSetShader(m_vertexShader, nullptr, 0);
	IRenderer::getRenderDevice()->getDeviceContext()->IASetInputLayout(m_inputLayout);
}