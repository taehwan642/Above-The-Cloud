#include "DXUT.h"
#include "../Engine/Transform.h"
#include "test.h"
#include "Camera.h"

Camera::Camera(void)
{
	transformcomponent = new Engine::Transform();
	componentgroup.emplace(L"Transform", transformcomponent);
}

Camera::~Camera(void)
{
}

void Camera::Update(const float& dt)
{
	GameObject::Update(dt);
}

void Camera::LateUpdate(const FLOAT& dt)
{
	D3DXMATRIX matView;
	D3DXMatrixInverse(&matView, 0, &transformcomponent->worldMatrix);

	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj,
		D3DXToRadian(70),
		static_cast<float>(DXUTGetD3D9BackBufferSurfaceDesc()->Width) /
		static_cast<float>(DXUTGetD3D9BackBufferSurfaceDesc()->Height),
		1, 500);
	DEVICE->SetTransform(D3DTS_VIEW, &matView);
	DEVICE->SetTransform(D3DTS_PROJECTION, &matProj);

	GameObject::LateUpdate(dt);
}

void Camera::Render(const FLOAT& dt)
{
	GameObject::Render(dt);
}

void Camera::Free(void)
{
	GameObject::Free();
}
