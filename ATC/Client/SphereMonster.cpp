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
#include "SphereMonster.h"

bool testcase = false;

SphereMonster::SphereMonster(void)
{
	shader = dynamic_cast<Engine::Shader*>(Engine::ResourceManager::GetInstance()->LoadResource(L"dyshader"));
	mesh = dynamic_cast<Engine::DynamicMesh*>(Engine::ResourceManager::GetInstance()->LoadResource(L"Monster1"));
	componentgroup.emplace(L"Shader", shader);
	componentgroup.emplace(L"Mesh", mesh);
	transform = new Engine::Transform();
	componentgroup.emplace(L"Transform", transform);
	transform->scale = { 0.1f, 0.1f, 0.1f };
	transform->position = { 10,10,10 };

	observer = new PlayerObserver();
	Engine::SubjectManager::GetInstance()->Subscribe(observer);
	Engine::SubjectManager::GetInstance()->Notify(static_cast<UINT>(PlayerInfos::PLAYERTRANSFORM));

	collider = new Engine::Collider(3, &transform->position);
	Engine::CollisionManager::GetInstance()->PushData(MONSTER, this);
	componentgroup.emplace(L"collider", collider);
	colliderdata.center = &transform->position;
	colliderdata.radius = 3;
	colliderdata.tag = L"monster1";
	colliderdata.ishit = false;

	UINT temp = 1;
	mesh->SetAnimationSet(temp);
}

SphereMonster::~SphereMonster(void)
{
}

void SphereMonster::Movement(void)
{
	// 1. Rand
	// 2. SEt
	// 3. Play

	//transform->position = 
}

void SphereMonster::Update(const FLOAT& dt)
{
	// 나와 플레이어의 방향을 구한다.
	// 내 forward와 내적한다.
	D3DXVECTOR3 look = observer->GetTransform()->position - transform->position;
	D3DXVec3Normalize(&look, &look);
	look *= -1.f;

	//  up과 look외적 => right
	D3DXVECTOR3 right;
	D3DXVec3Cross(&right, &D3DXVECTOR3(0, 1, 0), &look);
	D3DXVec3Normalize(&right, &right);

	//right *= -1.f;

	// look과 right 외적 => up
	D3DXVECTOR3 up;
	D3DXVec3Cross(&up, &look, &right);
	D3DXVec3Normalize(&up, &up);

	D3DXMATRIX matRot;
	D3DXMatrixIdentity(&matRot);
	memcpy(&matRot._11, &right, sizeof(D3DXVECTOR3));
	memcpy(&matRot._21, &up, sizeof(D3DXVECTOR3));
	memcpy(&matRot._31, &look, sizeof(D3DXVECTOR3));
	D3DXQuaternionRotationMatrix(&transform->quaternion, &matRot);

	if (!testcase)
	{
		movementqueue.emplace([=]()-> bool
			{
				return transform->Vec3Lerp(transform->position, D3DXVECTOR3(50, 50, 50), dt / 20);
			});
		movementqueue.emplace([=]()-> bool
			{
				return transform->Vec3Lerp(transform->position, D3DXVECTOR3(-50, -50, 50), dt / 20);
			});
		movementqueue.emplace([=]()-> bool
			{
				return transform->Vec3Lerp(transform->position, D3DXVECTOR3(50, 50, 50), dt / 20);
			});
		testcase = true;
	}

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
	shader->SetupTable(transform->worldMatrix);
	UINT pass = 0;
	LPD3DXEFFECT tempeffect = shader->GetEffect();
	tempeffect->Begin(&pass, 0);
	tempeffect->BeginPass(0);
	mesh->RenderMesh(tempeffect);
	tempeffect->EndPass();
	tempeffect->End();

	collider->RenderCollider();

	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	MonsterBase::Render(dt);
}

void SphereMonster::Free(void)
{
	Engine::SubjectManager::GetInstance()->UnSubscribe(observer);
	observer->Release();
	MonsterBase::Free();
}
