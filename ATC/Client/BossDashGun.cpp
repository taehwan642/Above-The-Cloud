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

BossDashGun::BossDashGun(void)
{
	shader = dynamic_cast<Engine::Shader*>(Engine::ResourceManager::GetInstance()->LoadResource(L"dyshader"));
	mesh = dynamic_cast<Engine::DynamicMesh*>(Engine::ResourceManager::GetInstance()->LoadResource(L"BossDashGun"));
	componentgroup.emplace(L"Shader", shader);
	componentgroup.emplace(L"Mesh", mesh);
	transform = new Engine::Transform();
	componentgroup.emplace(L"Transform", transform);
	transform->scale = { 0.15f, 0.15f, 0.15f };
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

BossDashGun::~BossDashGun(void)
{
}

void BossDashGun::SetInformation(const D3DXVECTOR3& _position)
{
	BossGuns::SetInformation(_position);
}

void BossDashGun::Movement(const FLOAT& dt)
{
	if (isAttatched == false)
	{
		movementspeed = 1.f;
		int movementindex = rand() % 2;
		movementindex = 1;
		// 보고있는 방향으로 Dash하거나
		if (movementindex == 0)
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
	
		// 총한발 쏘기
		else
		{
			D3DXVECTOR3 dir = *reinterpret_cast<D3DXVECTOR3*>(&transform->worldMatrix._31);
			std::cout << dir.x << " " << dir.y << " " << dir.z << std::endl;
			movementqueue.emplace([=]()->bool
				{
					currentState = MONSTERSHOOT;
					mesh->SetAnimationSet(currentState);
					delta += dt;
					if (delta < 2.f)
					{
						transform->localPosition += dir * 5;
					}
					else
					{
						delta = 0;
						return true;
					}
					return false;
				});
			movementspeed = 3.f;
		}
	}
}

INT BossDashGun::Update(const FLOAT& dt)
{
	BossGuns::Update(dt);
	return OBJALIVE;
}

void BossDashGun::LateUpdate(const FLOAT& dt)
{
	BossGuns::LateUpdate(dt);
}

void BossDashGun::Render(const FLOAT& dt)
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
	BossGuns::Render(dt);
}

void BossDashGun::Free(void)
{
	Engine::SubjectManager::GetInstance()->UnSubscribe(observer);
	observer->Release();
	BossGuns::Free();
}
