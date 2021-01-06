#include "DXUT.h"
#include "../Engine/Transform.h"
#include "../Engine/DynamicMesh.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/SubjectManager.h"
#include "../Engine/Shader.h"
#include "../Engine/Trail.h"
#include "PlayerObserver.h"
#include "SphereMonster.h"

SphereMonster::SphereMonster(void)
{
	shader = dynamic_cast<Engine::Shader*>(Engine::ResourceManager::GetInstance()->LoadResource(L"dyshader"));
	mesh = dynamic_cast<Engine::DynamicMesh*>(Engine::ResourceManager::GetInstance()->LoadResource(L"Monster1"));
	componentgroup.emplace(L"Shader", shader);
	componentgroup.emplace(L"Mesh", mesh);
	transform = new Engine::Transform();
	componentgroup.emplace(L"Transform", transform);
	transform->position = { 10,10,10 };
	UINT temp = 1;
	mesh->SetAnimationSet(temp);
}

SphereMonster::~SphereMonster(void)
{
}

void SphereMonster::Movement(void)
{
}

void SphereMonster::Update(const FLOAT& dt)
{
	MonsterBase::Update(dt);
}

void SphereMonster::LateUpdate(const FLOAT& dt)
{
	MonsterBase::LateUpdate(dt);
}

void SphereMonster::Render(const FLOAT& dt)
{
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	mesh->PlayAnimation(dt);
	mesh->RenderMesh();
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	MonsterBase::Render(dt);
}

void SphereMonster::Free(void)
{
}
