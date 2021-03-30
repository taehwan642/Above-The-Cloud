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
#include "MonsterBullet.h"
#include "../Engine/ObjectManager.h"
#include "Monster1.h"

bool testcase = false;

Monster1::Monster1(void)
{
	shader = dynamic_cast<Engine::Shader*>(Engine::ResourceManager::GetInstance()->LoadResource(L"dyshader"));
	mesh = dynamic_cast<Engine::DynamicMesh*>(Engine::ResourceManager::GetInstance()->LoadResource(L"Monster1"));
	componentgroup.emplace(L"Shader", shader);
	componentgroup.emplace(L"Mesh", mesh);
	transform = new Engine::Transform();
	componentgroup.emplace(L"Transform", transform);
	transform->scale = { 0.1f, 0.1f, 0.1f };
	transform->localPosition = { 0,0,-30 };
	observer = new PlayerObserver();
	Engine::SubjectManager::GetInstance()->Subscribe(observer);
	Engine::SubjectManager::GetInstance()->Notify(static_cast<UINT>(PlayerInfos::PLAYERTRANSFORM));

	collider = new Engine::Collider(3, &transform->localPosition);
	componentgroup.emplace(L"collider", collider);
	colliderdata.center = &transform->localPosition;
	colliderdata.radius = 3;
	colliderdata.tag = L"Monster";
	currentState = 0;
	mesh->SetAnimationSet(currentState);
}

Monster1::~Monster1(void)
{
}

void Monster1::SetInformation(const D3DXVECTOR3& _position)
{
	Engine::CollisionManager::GetInstance()->PushData(MONSTER, this);
	MonsterBase::SetInformation(_position);
}

void Monster1::Movement(const FLOAT& dt)
{
	movementspeed = 2.f;

	int s = rand() % 2;
	if (s == 0)
	{
		currentState = MONSTERSHOOT;
		mesh->SetAnimationSet(currentState);
		D3DXVECTOR3 dir = -*reinterpret_cast<D3DXVECTOR3*>(&transform->worldMatrix._31);


		MonsterBullet* m = Engine::ObjectManager::GetInstance()->CheckActiveFalsedObjectAndSpawn<MonsterBullet>(OBJ2, L"MONSTERBULLET");
		m->SetInformation(transform->localPosition, dir);
	}
	else if (s == 1)
	{
		FLOAT x = (rand() % 100) - (rand() % 50);
		FLOAT y = (rand() % 100) - (rand() % 50);
		while (y <= -50)
			y = (rand() % 100) - (rand() % 50);
		FLOAT z = (rand() % 100) - (rand() % 50);
		movementqueue.emplace([=]()-> bool
			{
				return transform->Lerp(transform->localPosition, D3DXVECTOR3(x, y, z), dt, 10);
			});
	}
}

INT Monster1::Update(const FLOAT& dt)
{
	D3DXVECTOR3 look = observer->GetTransform()->localPosition - transform->localPosition;
	D3DXVec3Normalize(&look, &look);
	look *= -1.f;

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

	ObjectState state = static_cast<ObjectState>(MonsterBase::Update(dt));

	return OBJALIVE;
}

void Monster1::LateUpdate(const FLOAT& dt)
{
	MonsterBase::LateUpdate(dt);
}

void Monster1::Render(const FLOAT& dt)
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

void Monster1::Free(void)
{
	Engine::SubjectManager::GetInstance()->UnSubscribe(observer);
	observer->Release();
	MonsterBase::Free();
}
