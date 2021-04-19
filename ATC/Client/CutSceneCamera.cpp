#include "DXUT.h"
#include "../Engine/Camera.h"
#include "../Engine/Transform.h"
#include "CutSceneCamera.h"

CutSceneCamera::CutSceneCamera(void)
{
	transform = new Engine::Transform();
	componentgroup.emplace(L"Transform", transform);
	camera = new Engine::Camera();
	componentgroup.emplace(L"Camera", camera);
	camera->SetProjectionMatrix(D3DXToRadian(70),
		static_cast<FLOAT>(DXUTGetD3D9BackBufferSurfaceDesc()->Width) /
		static_cast<FLOAT>(DXUTGetD3D9BackBufferSurfaceDesc()->Height),
		1,
		500);
}

CutSceneCamera::~CutSceneCamera(void)
{
}

INT CutSceneCamera::Update(const FLOAT& dt)
{
	return GameObject::Update(dt);
}

void CutSceneCamera::LateUpdate(const FLOAT& dt)
{
	
	camera->Render(dt);
	GameObject::LateUpdate(dt);
}

void CutSceneCamera::Render(const FLOAT& dt)
{
	GameObject::Render(dt);
}

void CutSceneCamera::Free(void)
{
	GameObject::Free();
}
