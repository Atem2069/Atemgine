#pragma once

#include <DirectXMath.h>
using namespace DirectX;

inline XMFLOAT3 operator*(XMFLOAT3 a, XMFLOAT3 b)
{
	a.x *= b.x;
	a.y *= b.y;
	a.z *= b.z;
	return a;
}

inline XMFLOAT3 operator*(XMFLOAT3 a, float b)
{
	a.x *= b;
	a.y *= b;
	a.z *= b;
	return a;
}

inline XMFLOAT3 operator+(XMFLOAT3 a, XMFLOAT3 b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return a;
}

inline XMFLOAT3& operator+=(XMFLOAT3& a, XMFLOAT3 b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return a;
}

inline XMFLOAT3& operator-=(XMFLOAT3& a, XMFLOAT3 b)
{
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
	return a;
}

inline XMFLOAT3 operator-(XMFLOAT3 a, XMFLOAT3 b)
{
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
	return a;
}

inline XMFLOAT3 cross(XMFLOAT3 a, XMFLOAT3 b)
{
	XMVECTOR temp1 = XMLoadFloat3(&a);
	XMVECTOR temp2 = XMLoadFloat3(&b);
	temp2 = XMVector3Normalize(XMVector3Cross(temp1, temp2));
	XMFLOAT3 res;
	XMStoreFloat3(&res, temp2);
	return res;
}
