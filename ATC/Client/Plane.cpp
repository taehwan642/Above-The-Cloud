#include "DXUT.h"
#include "../Engine/Transform.h"
#include "../Engine/StaticMesh.h"
#include "../Engine/DynamicMesh.h"
#include "../Engine/Shader.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/SubjectManager.h"
#include "../Engine/Trail.h"
#include "../Engine/RaycastManager.h"
#include "../Engine/ObjectManager.h"
#include "../Engine/EffectManager.h"
#include "../Engine/TextureEffect.h"
#include "../Engine/Collider.h"
#include "../Engine/CollisionManager.h"
#include "../Engine/ObjectManager.h"
#include "Missile.h"
#include "Plane.h"

bool testfly = true;
Plane::Plane(void)
{
	testshader = dynamic_cast<Engine::Shader*>(Engine::ResourceManager::GetInstance()->LoadResource(L"dyshader"));
	testdynamic = dynamic_cast<Engine::DynamicMesh*>(Engine::ResourceManager::GetInstance()->LoadResource(L"dynamic"));
	componentgroup.emplace(L"shader", testshader);
	componentgroup.emplace(L"DynamicMesh", testdynamic);

	transform = new Engine::Transform();
	componentgroup.emplace(L"Transform", transform);

	Engine::SubjectManager::GetInstance()->AddData(static_cast<UINT>(PlayerInfos::PLAYERTRANSFORM), transform);
	Engine::SubjectManager::GetInstance()->AddData(static_cast<UINT>(PlayerInfos::PLAYERHEALTH), &healthpoint);
	Engine::SubjectManager::GetInstance()->AddData(static_cast<UINT>(PlayerInfos::PLAYERMISSILELOCKOBJECT), dstObject);

	testdynamic->SetParent(&transform->worldMatrix);

	transform->scale = D3DXVECTOR3(0.01, 0.01, 0.01);

	UINT aniset = 1;
	testdynamic->SetAnimationSet(aniset);

	lefttrail = new Engine::Trail();
	lefttrail->Initalize(&transform->worldMatrix, 1024, 0.03f, 4, 3, L"TrailTexture");
	componentgroup.emplace(L"trail", lefttrail);

	righttrail = new Engine::Trail();
	righttrail->Initalize(&transform->worldMatrix, 1024, 0.03f, 4, 3, L"TrailTexture");
	componentgroup.emplace(L"trail2", righttrail);

	lefttrailpos[0] = { 0,0,0 };
	lefttrailpos[1] = { 0,0,0 };
	righttrailpos[0] = { 0,0,0 };
	righttrailpos[1] = { 0,0,0 };

	effectpos[0] = { -190 , -15, -300 };
	effectpos[1] = { -125 , -15, -300 };
	effectpos[2] = { 125 , -15, -300 };
	effectpos[3] = { 190 , -15, -300 };

	collider = new Engine::Collider(1, &transform->position);
	Engine::CollisionManager::GetInstance()->PushData(PLAYER, this);
	componentgroup.emplace(L"collider", collider);
	colliderdata.center = &transform->position;
	colliderdata.radius = 1;
	colliderdata.tag = L"player";
}

Plane::~Plane(void)
{
}

void Plane::CollisionEvent(const std::wstring& _objectTag, GameObject* _gameObject)
{
	if (_objectTag == L"MonsterBullet" || _objectTag == L"Monster")
	{
		if (invincibletime <= 0)
		{
			--healthpoint;
			Engine::SubjectManager::GetInstance()->Notify(static_cast<UINT>(PlayerInfos::PLAYERHEALTH));
			invincibletime = 1.f;
		}
	}
}

INT Plane::Update(const FLOAT& dt)
{
	GameObject::Update(dt);

	invincibletime -= dt;

	D3DXVec3TransformCoord(&lefttrailpos[0], &D3DXVECTOR3(509, -22, -189), &transform->worldMatrix);
	D3DXVec3TransformCoord(&lefttrailpos[1], &D3DXVECTOR3(490, -15, -189), &transform->worldMatrix);
	D3DXVec3TransformCoord(&righttrailpos[0], &D3DXVECTOR3(-509, -22, -189), &transform->worldMatrix);
	D3DXVec3TransformCoord(&righttrailpos[1], &D3DXVECTOR3(-490, -15, -189), &transform->worldMatrix);

	lefttrail->AddNewTrail(lefttrailpos[0], lefttrailpos[1], dt);
	righttrail->AddNewTrail(righttrailpos[0], righttrailpos[1], dt);

	directionVector = -(*reinterpret_cast<D3DXVECTOR3*>(&transform->worldMatrix._31));

	if (DXUTWasKeyPressed('U'))
	{
		UINT aniset = testfly ? 0 : 1;
		testfly = !testfly;
		testdynamic->SetAnimationSet(aniset);
	}

	if (DXUTIsKeyDown('W'))
		transform->Rotate(Engine::Transform::RotType::RIGHT, 1.0f * dt);

	if (DXUTIsKeyDown('S'))
		transform->Rotate(Engine::Transform::RotType::RIGHT, -1.0f * dt);

	if (DXUTIsKeyDown('A'))
		transform->Rotate(Engine::Transform::RotType::LOOK, -2.5f * dt);

	if (DXUTIsKeyDown('D'))
		transform->Rotate(Engine::Transform::RotType::LOOK, 2.5f * dt);

	transform->position += directionVector * dt * 1000;

	
	return OBJALIVE;
}

void Plane::LateUpdate(const FLOAT& dt)
{
	float a;
	D3DXVECTOR3 p;

	if (DXUTIsKeyDown(VK_SPACE))
	{
		for (int i = 0; i < 4; ++i)
			Engine::EffectManager::GetInstance()->
			SpawnTextureEffect(effectpos[i], transform, 0.3f, L"muzzleFlash");
		if (Engine::CollisionManager::GetInstance()->MouseRaySphereInteresection(a, p, MONSTER))
		{
			D3DXVECTOR3 dir = -*reinterpret_cast<D3DXVECTOR3*>(&transform->worldMatrix._31);
			D3DXVECTOR3 pos = *reinterpret_cast<D3DXVECTOR3*>(&transform->worldMatrix._41);

			float angle = 0;
			D3DXVECTOR3 direc = pos - p;
			D3DXVec3Normalize(&direc, &direc);
			D3DXVec3Normalize(&dir, &dir);
			angle = D3DXVec3Dot(&dir, &direc);
			if (angle < -0.31f)
			{
				GameObject* g = Engine::CollisionManager::GetInstance()->dstObject;
				g->CollisionEvent(L"PlayerShoot", this);
			}

		}
	}

	if (DXUTWasKeyPressed('E'))
	{
		Missile* m = Engine::ObjectManager::GetInstance()->GetActiveFalsedObject<Missile>(L"테스트", L"BULLET");

		if (m == nullptr)
			Engine::ObjectManager::GetInstance()->AddObjectAtLayer<Missile>(L"테스트", L"BULLET");
		else
		{
			m->SetActive(true);
			m->Initalize();
		}
	}

	D3DXVec3Normalize(&directionVector, &directionVector);
	dstObject = Engine::CollisionManager::GetInstance()->GetClosestObject(MONSTER, transform->position,
		directionVector, -0.61f);
	Engine::SubjectManager::GetInstance()->SetData(static_cast<UINT>(PlayerInfos::PLAYERMISSILELOCKOBJECT), dstObject);
	

	GameObject::LateUpdate(dt);
}

void Plane::Render(const FLOAT& dt)
{
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	testdynamic->PlayAnimation(dt * 3);
	testshader->SetupTable(transform->worldMatrix);
	UINT pass = 0;
	LPD3DXEFFECT tempeffect = testshader->GetEffect();
	tempeffect->SetVector((D3DXHANDLE)L"lightposition", &worldLightPosition);
	tempeffect->SetVector((D3DXHANDLE)L"cameraposition", &worldCameraPosition);
	tempeffect->Begin(&pass, 0);
	tempeffect->BeginPass(0);
	testdynamic->RenderNoSkinnedMesh(tempeffect);
	tempeffect->EndPass();
	tempeffect->End();

	collider->RenderCollider();

	GameObject::Render(dt);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void Plane::Free(void)
{
	GameObject::Free();
}
