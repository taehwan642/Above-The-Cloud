#include "DXUT.h"
#include "../Engine/Transform.h"
#include "MenuCamera.h"

MenuCamera::MenuCamera(void)
{
	transform = new Engine::Transform();
	componentgroup.emplace(L"Transform", transform);
}

MenuCamera::~MenuCamera(void)
{
}

INT MenuCamera::Update(const FLOAT& dt)
{
	return GameObject::Update(dt);
}

void MenuCamera::LateUpdate(const FLOAT& dt)
{
	D3DXMATRIX matView, matProj;
	D3DXMatrixInverse(&matView, 0, &transform->worldMatrix);
	D3DXMatrixPerspectiveFovLH(&matProj,
		D3DXToRadian(70),
		static_cast<float>(DXUTGetD3D9BackBufferSurfaceDesc()->Width) /
		static_cast<float>(DXUTGetD3D9BackBufferSurfaceDesc()->Height),
		1, 500);
	DEVICE->SetTransform(D3DTS_VIEW, &matView);
	DEVICE->SetTransform(D3DTS_PROJECTION, &matProj);

	GameObject::LateUpdate(dt);
}

void MenuCamera::Render(const FLOAT& dt)
{
	GameObject::Render(dt);
}

void MenuCamera::Free(void)
{
	GameObject::Free();
}
