#pragma once

#include <DirectXMath.h>
using namespace DirectX;

struct CameraInfo
{
	XMMATRIX projection;
	XMMATRIX view;
};

class ICamera
{
public:
	ICamera(float width, float height, float fov);

	void update(XMFLOAT3 position, XMFLOAT3 dir);

	CameraInfo getCameraMatrices();
private:
	CameraInfo m_cameraInfo;
};