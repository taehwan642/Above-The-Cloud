#include "DXUT.h"
#include "../Engine/Transform.h"
#include "../Engine/Camera.h"
#include "MenuCamera.h"

MenuCamera::MenuCamera(void)
{
	transform = new Engine::Transform();
	camera = new Engine::Camera();
	componentgroup.emplace(L"Transform", transform);
	componentgroup.emplace(L"Camera", camera);
	camera->SetProjectionMatrix(D3DXToRadian(70),
								static_cast<FLOAT>(DXUTGetD3D9BackBufferSurfaceDesc()->Width) /
								static_cast<FLOAT>(DXUTGetD3D9BackBufferSurfaceDesc()->Height),
								1,
								500);
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
	D3DXMATRIX matView;
	D3DXMatrixInverse(&matView, 0, &transform->worldMatrix);
	camera->SetViewMatrix(matView);
	camera->Render(dt);
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
