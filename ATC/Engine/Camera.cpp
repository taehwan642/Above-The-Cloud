#include "DXUT.h"
#include "Camera.h"

USING(Engine)

void Camera::SetProjectionMatrix(const D3DXMATRIX& _projectionMatrix)
{
	projectionMatrix = _projectionMatrix;
}

void Camera::SetProjectionMatrix(const FLOAT& _fov, const FLOAT& _aspect, const FLOAT& _zn, const FLOAT& _zf)
{
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, _fov, _aspect, _zn, _zf);
	DEVICE->SetTransform(D3DTS_PROJECTION, &projectionMatrix); // Device의 Setting이 변경되지 않는다면, (Fov 도는 Aspect같은 창 크기에 변동이 일어나지 않는다면) 초기화때만 세팅해주면 됨.
}

void Camera::SetViewMatrix(const D3DXMATRIX& _viewMatrix)
{
	viewMatrix = _viewMatrix;
}

Camera::Camera(void)
{
	D3DXMatrixIdentity(&viewMatrix);
	D3DXMatrixIdentity(&projectionMatrix);
}

void Camera::Update(const FLOAT& dt)
{

}

void Camera::Render(const FLOAT& dt)
{
	DEVICE->SetTransform(D3DTS_VIEW, &viewMatrix);
}

void Camera::ResetDevice(void)
{
	DEVICE->SetTransform(D3DTS_PROJECTION, &projectionMatrix);
}

void Camera::Free(void)
{

}
