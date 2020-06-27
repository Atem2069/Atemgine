#pragma once

#include "..\base\ConstantBufferBase.h"
#include <d3d11.h>

class IDirect3D11ConstantBuffer : public IConstantBufferBase
{
protected:
	bool APIInitialize(ConstantBufferUploadInfo bufferData);
	void APIDestroy();

	void APIBind(ConstBufferBindingLocation bindingLocation, int binding);

	bool APIUpdate(ConstantBufferUploadInfo bufferData);
private:
	ID3D11Buffer* m_constantBuffer;
};