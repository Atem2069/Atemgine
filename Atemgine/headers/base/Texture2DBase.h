#pragma once

enum TextureFormat
{
	FORMAT_R8G8B8A8_UNORM,
	FORMAT_R32G32B32A32_FLOAT,
	FORMAT_D24_UNORM_S8_UINT
};

enum TextureUsage
{
	USAGE_SHADER_READ = 1,
	USAGE_SHADER_WRITE = 2,
	USAGE_UNORDERED_ACCESS = 4
};

struct Texture2DUploadInfo
{
	void* rawData;
	size_t rowSizeBytes;	//x * sizeof pixel 
	TextureFormat format;
	TextureUsage usage;
};

class ITexture2DBase
{
public:
	virtual bool init(Texture2DUploadInfo texData) = 0;
	virtual void destroy() = 0;

	virtual void setBinding(int binding) = 0;
	virtual void bind() = 0;
};