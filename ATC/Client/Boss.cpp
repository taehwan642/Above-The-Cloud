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
#include "../Engine/ObjectManager.h"
#include "BossDashGun.h"
#include "BossShootGun.h"
#include "Boss.h"

Boss::Boss(void)
{
	shader = dynamic_cast<Engine::Shader*>(Engine::ResourceManager::GetInstance()->LoadResource(L"dyshader"));
	mesh = dynamic_cast<Engine::DynamicMesh*>(Engine::ResourceManager::GetInstance()->LoadResource(L"Boss"));
	componentgroup.emplace(L"Shader", shader);
	componentgroup.emplace(L"Mesh", mesh);
	transform = new Engine::Transform();
	componentgroup.emplace(L"Transform", transform);
	transform->scale = { 0.1f, 0.1f, 0.1f };
	transform->position = { 0,0,-30 };
	observer = new PlayerObserver();
	Engine::SubjectManager::GetInstance()->Subscribe(observer);
	Engine::SubjectManager::GetInstance()->Notify(static_cast<UINT>(PlayerInfos::PLAYERTRANSFORM));

	collider = new Engine::Collider(3, &transform->position);
	componentgroup.emplace(L"collider", collider);
	colliderdata.center = &transform->position;
	colliderdata.radius = 3;
	colliderdata.tag = L"Monster";
	currentState = MONSTERIDLE;
	mesh->SetAnimationSet(currentState);

	Hp = 10;
	FullHP = 10;

	bossDashgunTop = new BossDashGun;
	bossDashgunTop->SetInformation({ 0,20,0 });
	bossDashgunBottom = new BossDashGun;
	bossDashgunBottom->SetInformation({ 0,50,0 });
}

Boss::~Boss(void)
{
}

void Boss::Movement(const FLOAT& dt)
{
}

INT Boss::Update(const FLOAT& dt)
{
	bossDashgunTop->Update(dt);
	bossDashgunBottom->Update(dt);
	MonsterBase::Update(dt);
	return OBJALIVE;
}

void Boss::LateUpdate(const FLOAT& dt)
{
	D3DXVECTOR3 look = observer->GetTransform()->position - transform->position;
	D3DXVec3Normalize(&look, &look);

	D3DXVECTOR3 right;
	D3DXVec3Cross(&right, &D3DXVECTOR3(0, 1, 0), &look);
	D3DXVec3Normalize(&right, &right);

	D3DXVECTOR3 up;
	D3DXVec3Cross(&up, &look, &right);
	D3DXVec3Normalize(&up, &up);

	D3DXMATRIX matRot;
	D3DXMatrixIdentity(&matRot);
	memcpy(&matRot._11, &right, sizeof(D3DXVECTOR3));
	memcpy(&matRot._21, &up, sizeof(D3DXVECTOR3));
	memcpy(&matRot._31, &look, sizeof(D3DXVECTOR3));
	D3DXQuaternionRotationMatrix(&transform->quaternion, &matRot);
	bossDashgunTop->LateUpdate(dt);
	bossDashgunBottom->LateUpdate(dt);
	MonsterBase::LateUpdate(dt);
}

void Boss::Render(const FLOAT& dt)
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
	bossDashgunTop->Render(dt);
	bossDashgunBottom->Render(dt);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	MonsterBase::Render(dt);
}

void Boss::Free(void)
{
	Engine::SubjectManager::GetInstance()->UnSubscribe(observer);
	observer->Release();
	Safe_Release(bossDashgunTop);
	Safe_Release(bossDashgunBottom);
	MonsterBase::Free();
}
