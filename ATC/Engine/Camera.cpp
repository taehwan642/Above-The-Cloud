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
	DEVICE->SetTransform(D3DTS_PROJECTION, &projectionMatrix); // Device�� Setting�� ������� �ʴ´ٸ�, (Fov ���� Aspect���� â ũ�⿡ ������ �Ͼ�� �ʴ´ٸ�) �ʱ�ȭ���� �������ָ� ��.
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
