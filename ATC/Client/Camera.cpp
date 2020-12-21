#include "DXUT.h"
#include "../Engine/Transform.h"
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

void Camera::LateUpdate(void)
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

	GameObject::LateUpdate();
}

void Camera::Render(void)
{
	GameObject::Render();
}

void Camera::Free(void)
{
	GameObject::Free();
}
