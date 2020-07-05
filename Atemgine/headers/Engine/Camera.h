#pragma once

#include <DirectXMath.h>
using namespace DirectX;

#include "..\Renderer.h"
#include "Misc\MathHelpers.h"

struct CameraInfo
{
	XMMATRIX projection;
	XMMATRIX view;
};

class ICamera
{
public:
	ICamera(float width, float height, float fov);

	void update();
	void update(XMFLOAT3 position, XMFLOAT3 dir);

	CameraInfo getCameraMatrices();
private:
	XMFLOAT3 m_currentPosition;
	XMFLOAT3 m_currentDirection;
	float m_pitch, m_yaw;
	CameraInfo m_cameraInfo;
};