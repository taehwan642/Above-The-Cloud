#include "DXUT.h"
#include "../Engine/Transform.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/StaticMesh.h"
#include "../Engine/CollisionManager.h"
#include "../Engine/Collider.h"
#include "../Engine/Trail.h"
#include "Missile.h"

Missile::Missile(void)
{
	transform = new Engine::Transform();
	componentgroup.emplace(L"transform", transform);
	mesh = dynamic_cast<Engine::StaticMesh*>(Engine::ResourceManager::GetInstance()->LoadResource(L"Missile"));
	collider = new Engine::Collider(1, &transform->position, ObjectTag::PLAYER);
	Engine::CollisionManager::GetInstance()->PushData(collider);
	componentgroup.emplace(L"collider", collider);
}

Missile::~Missile(void)
{

}

void Missile::Update(const FLOAT& dt)
{
	GameObject::Update(dt);
}

void Missile::LateUpdate(const FLOAT& dt)
{

	GameObject::LateUpdate(dt);
}

void Missile::Render(const FLOAT& dt)
{
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	mesh->RenderMesh();
	collider->RenderCollider();
	GameObject::Render(dt);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void Missile::Free(void)
{
	GameObject::Free();
}
