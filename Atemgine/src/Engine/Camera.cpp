#include "..\..\headers\Engine\Camera.h"

ICamera::ICamera(float width, float height, float fov)
{
	m_cameraInfo = {};
	m_cameraInfo.projection = XMMatrixPerspectiveFovLH(fov, width / height, 0.01f, 10000.0f);
	m_cameraInfo.view = XMMatrixIdentity();
}

void ICamera::update(XMFLOAT3 position, XMFLOAT3 dir)
{
	XMVECTOR tempPos = XMLoadFloat3(&position);
	XMVECTOR tempDir = tempPos + XMLoadFloat3(&dir);
	m_cameraInfo.view = XMMatrixLookAtLH(tempPos,tempDir, XMVectorSet(0, 1, 0, 1));
}

CameraInfo ICamera::getCameraMatrices()
{
	return m_cameraInfo;
}