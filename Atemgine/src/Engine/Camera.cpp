#include "..\..\headers\Engine\Camera.h"

ICamera::ICamera(float width, float height, float fov)
{
	m_cameraInfo = {};
	m_cameraInfo.projection = XMMatrixPerspectiveFovLH(fov, width / height, 0.01f, 10000.0f);
	m_cameraInfo.view = XMMatrixIdentity();

	m_currentPosition = {};
	m_currentDirection = XMFLOAT3(0, 0, 1);
	m_pitch = 0; m_yaw = 0;
}

void ICamera::update()
{
	static float cameraSpeed = 200.0f;
	IRenderer* current = IRenderer::getCurrentInstance();
	float deltaTime = current->deltaTime();

	if (GetAsyncKeyState(VK_SPACE))
		m_currentPosition.y += cameraSpeed * deltaTime;
	if (GetAsyncKeyState(VK_LSHIFT))
		m_currentPosition.y -= cameraSpeed * deltaTime;
	if (GetAsyncKeyState('W'))
		m_currentPosition += m_currentDirection * cameraSpeed * deltaTime;
	if (GetAsyncKeyState('S'))
		m_currentPosition -= m_currentDirection * cameraSpeed * deltaTime;
	if (GetAsyncKeyState('A'))
		m_currentPosition += cross(m_currentDirection,XMFLOAT3(0,1,0)) * cameraSpeed * deltaTime;
	if (GetAsyncKeyState('D'))
		m_currentPosition -= cross(m_currentDirection,XMFLOAT3(0,1,0)) * cameraSpeed * deltaTime;
	if (GetAsyncKeyState(VK_LEFT))
		m_yaw += cameraSpeed * deltaTime;
	if (GetAsyncKeyState(VK_RIGHT))
		m_yaw -= cameraSpeed * deltaTime;
	if (GetAsyncKeyState(VK_UP))
		m_pitch += cameraSpeed * deltaTime;
	if (GetAsyncKeyState(VK_DOWN))
		m_pitch -= cameraSpeed * deltaTime;

	m_currentDirection.x = XMScalarCos(XMConvertToRadians(m_pitch)) * XMScalarCos(XMConvertToRadians(m_yaw));
	m_currentDirection.y = XMScalarSin(XMConvertToRadians(m_pitch));
	m_currentDirection.z = XMScalarCos(XMConvertToRadians(m_pitch)) * XMScalarSin(XMConvertToRadians(m_yaw));
	XMVECTOR temp = XMVector3Normalize(XMLoadFloat3(&m_currentDirection));	//epic directxmath hack
	XMStoreFloat3(&m_currentDirection, temp);


	this->update(m_currentPosition, m_currentDirection);

}

void ICamera::update(XMFLOAT3 position, XMFLOAT3 dir)
{
	XMVECTOR tempPos = XMLoadFloat3(&position);
	XMVECTOR tempDir = tempPos + XMLoadFloat3(&dir);
	m_cameraInfo.view = XMMatrixLookAtLH(tempPos,tempDir, XMVectorSet(0, 1, 0, 1));

	m_currentPosition = position;
	m_currentDirection = dir;
}

CameraInfo ICamera::getCameraMatrices()
{
	return m_cameraInfo;
}