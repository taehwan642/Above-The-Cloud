#include "DXUT.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/StaticMesh.h"
#include "../Engine/Transform.h"
#include "SkySphere.h"

SkySphere::SkySphere(void)
{
	transform = new Engine::Transform();
	transform->scale = { 0.7,0.7,0.7 };
	componentgroup.emplace(L"Transform", transform);
	skysphere = dynamic_cast<Engine::StaticMesh*>(Engine::ResourceManager::GetInstance()->LoadResource(L"SkySphere"));
	
}

SkySphere::~SkySphere(void)
{
}

void SkySphere::Update(const float& dt)
{
	GameObject::Update(dt);
}

void SkySphere::LateUpdate(const FLOAT& dt)
{
	GameObject::LateUpdate(dt);
}

void SkySphere::Render(const FLOAT& dt)
{
	DEVICE->SetTransform(D3DTS_WORLD, &transform->worldMatrix);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	skysphere->RenderMesh();
	GameObject::Render(dt);
}

void SkySphere::Free(void)
{
	GameObject::Free();
}
