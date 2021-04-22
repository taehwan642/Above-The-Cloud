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
#include "BossShootGun.h"

BossShootGun::BossShootGun(void)
{
	shader = dynamic_cast<Engine::Shader*>(Engine::ResourceManager::GetInstance()->LoadResource(L"dyshader"));
	mesh = dynamic_cast<Engine::DynamicMesh*>(Engine::ResourceManager::GetInstance()->LoadResource(L"BossShootGun"));
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

BossShootGun::~BossShootGun(void)
{
}

void BossShootGun::SetInformation(const D3DXVECTOR3& _position)
{
	BossGuns::SetInformation(_position);
}

void BossShootGun::Movement(const FLOAT& dt)
{
	// 보스랑 붙어있으면 X
	if (isAttatched == false)
	{
		int movementindex = rand() % 2;

		// 약한거 2개쏘거나
		if (movementindex == 0)
		{

		}

		// 총 큰거하나쏘거나 
		else
		{

		}
	}

}

INT BossShootGun::Update(const FLOAT& dt)
{
	BossGuns::Update(dt);
	return OBJALIVE;
}

void BossShootGun::LateUpdate(const FLOAT& dt)
{
	

	BossGuns::LateUpdate(dt);
}

void BossShootGun::Render(const FLOAT& dt)
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

void BossShootGun::Free(void)
{
	Engine::SubjectManager::GetInstance()->UnSubscribe(observer);
	observer->Release();
	BossGuns::Free();
}
