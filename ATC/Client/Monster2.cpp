#include "DXUT.h"
#include "../Engine/Transform.h"
#include "../Engine/DynamicMesh.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/SubjectManager.h"
#include "../Engine/Shader.h"
#include "../Engine/Trail.h"
#include "../Engine/CollisionManager.h"
#include "../Engine/Collider.h"
#include "PlayerObserver.h"
#include "Monster1.h"
#include "../Engine/ObjectManager.h"
#include "Monster2.h"

Monster2::Monster2(void)
{
	shader = dynamic_cast<Engine::Shader*>(Engine::ResourceManager::GetInstance()->LoadResource(L"dyshader"));
	mesh = dynamic_cast<Engine::DynamicMesh*>(Engine::ResourceManager::GetInstance()->LoadResource(L"Monster2"));
	componentgroup.emplace(L"Shader", shader);
	componentgroup.emplace(L"Mesh", mesh);
	transform = new Engine::Transform();
	componentgroup.emplace(L"Transform", transform);
	transform->scale = { 0.1f, 0.1f, 0.1f };
	transform->position = { 0,0,-30 };
	observer = new PlayerObserver();
	Engine::SubjectManager::GetInstance()->Subscribe(observer);
	Engine::SubjectManager::GetInstance()->Notify(static_cast<UINT>(PlayerInfos::PLAYERTRANSFORM));

	collider = new Engine::Collider(6, &transform->position);
	Engine::CollisionManager::GetInstance()->PushData(MONSTER, this);
	componentgroup.emplace(L"collider", collider);
	colliderdata.center = &transform->position;
	colliderdata.radius = 6;
	colliderdata.tag = L"Monster";
	currentState = MONSTERIDLE;
	mesh->SetAnimationSet(currentState);
}

Monster2::~Monster2(void)
{
}

void Monster2::Movement(const FLOAT& dt)
{
	movementspeed = 5.f;

	currentState = MONSTERSHOOT;
	mesh->SetAnimationSet(currentState);
	D3DXVECTOR3 dir = -*reinterpret_cast<D3DXVECTOR3*>(&transform->worldMatrix._31);
	D3DXVec3Normalize(&dir, &dir);
	D3DXVECTOR3 pos = transform->position + dir * 6;
	Monster1* m = Engine::ObjectManager::GetInstance()->GetActiveFalsedObject<Monster1>(OBJ2, L"Monster1");
	if (m == nullptr)
	{
		m = Engine::ObjectManager::GetInstance()->AddObjectAtLayer<Monster1>(OBJ2, L"Monster1");
		m->SetInformation(pos);
	}
	else
		m->SetInformation(pos);
}

INT Monster2::Update(const FLOAT& dt)
{
	MonsterBase::Update(dt);
	return OBJALIVE;
}

void Monster2::LateUpdate(const FLOAT& dt)
{
	MonsterBase::LateUpdate(dt);
}

void Monster2::Render(const FLOAT& dt)
{
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	mesh->PlayAnimation(dt);
	shader->SetupTable(transform->worldMatrix);
	UINT pass = 0;
	LPD3DXEFFECT tempeffect = shader->GetEffect();
	tempeffect->Begin(&pass, 0);
	tempeffect->BeginPass(0);
	mesh->RenderMesh(tempeffect);
	tempeffect->EndPass();
	tempeffect->End();
	//collider->RenderCollider();
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	MonsterBase::Render(dt);
}

void Monster2::Free(void)
{
	Engine::SubjectManager::GetInstance()->UnSubscribe(observer);
	observer->Release();
	MonsterBase::Free();
}
