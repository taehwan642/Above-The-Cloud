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
#include "test.h"

// FREE 되어야하는 컴포넌트들은 componentgroup 속에 들어있어야함.
bool testfly = true;
test::test(void)
{
	testshader = dynamic_cast<Engine::Shader*>(Engine::ResourceManager::GetInstance()->LoadResource(L"dyshader"));
	testdynamic = dynamic_cast<Engine::DynamicMesh*>(Engine::ResourceManager::GetInstance()->LoadResource(L"dynamic"));
	componentgroup.emplace(L"shader", testshader);

	transform = new Engine::Transform();
	componentgroup.emplace(L"Transform", transform);

	Engine::SubjectManager::GetInstance()->AddData(static_cast<UINT>(PlayerInfos::PLAYERTRANSFORM), transform);
	Engine::SubjectManager::GetInstance()->AddData(static_cast<UINT>(PlayerInfos::PLAYERHEALTH), &healthpoint);

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

	collider = new Engine::Collider(1, &transform->position, ObjectTag::PLAYER);
	Engine::CollisionManager::GetInstance()->PushData(PLAYER, this);
	componentgroup.emplace(L"collider", collider);
	colliderdata.center = &transform->position;
	colliderdata.radius = 1;
	colliderdata.tag = L"player";
	colliderdata.ishit = false;
}

test::~test(void)
{
}

void test::CollisionEvent(const wstring& _objectTag, GameObject* _gameObject)
{
	cout << "??!?!?!" << endl;
}

void test::Update(const float& dt)
{
	GameObject::Update(dt);
	D3DXVec3TransformCoord(&lefttrailpos[0], &D3DXVECTOR3(509, -22, -189), &transform->worldMatrix);
	D3DXVec3TransformCoord(&lefttrailpos[1], &D3DXVECTOR3(490, -15, -189), &transform->worldMatrix);
	D3DXVec3TransformCoord(&righttrailpos[0], &D3DXVECTOR3(-509, -22, -189), &transform->worldMatrix);
	D3DXVec3TransformCoord(&righttrailpos[1], &D3DXVECTOR3(-490, -15, -189), &transform->worldMatrix);

	lefttrail->AddNewTrail(lefttrailpos[0], lefttrailpos[1], dt);
	righttrail->AddNewTrail(righttrailpos[0], righttrailpos[1], dt);

	directonVector = -(*reinterpret_cast<D3DXVECTOR3*>(&transform->worldMatrix._31));

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

	if (DXUTWasKeyPressed('J'))
	{
		--healthpoint;
		Engine::SubjectManager::GetInstance()->Notify(static_cast<UINT>(PlayerInfos::PLAYERHEALTH));
	}

	if (invincibletime <= 0)
	{
		if (collider->ishit == true)
		{
			collider->ishit = false;
			--healthpoint;
			Engine::SubjectManager::GetInstance()->Notify(static_cast<UINT>(PlayerInfos::PLAYERHEALTH));
			invincibletime = 1.f;
		}
	}
	else
	{
		invincibletime -= dt;
		collider->ishit = false;
	}
	
	transform->position += directonVector * dt * 1000;
}

void test::LateUpdate(const FLOAT& dt)
{
	if (DXUTWasKeyPressed(VK_SPACE))
	{
		for(int i = 0; i < 4; ++i)
		Engine::EffectManager::GetInstance()->
			SpawnTextureEffect(effectpos[i], transform, 0.3f, L"muzzleFlash");
	}
	float a;
	D3DXVECTOR3 p;
	D3DXVECTOR3 dir = -*reinterpret_cast<D3DXVECTOR3*>(&transform->worldMatrix._31);
	D3DXVECTOR3 pos = *reinterpret_cast<D3DXVECTOR3*>(&transform->worldMatrix._41);
	D3DXMATRIX m = *Engine::EnemyManager::GetInstance()->enemyTransform[0];

	float angle = 0;
	D3DXVECTOR3 enpos = *reinterpret_cast<D3DXVECTOR3*>(&m._41);
	D3DXVECTOR3 direc = pos - enpos;
	D3DXVec3Normalize(&direc, &direc);
	D3DXVec3Normalize(&dir, &dir);
	angle = D3DXVec3Dot(&dir, &direc);
	if (angle < 0.91f)
		if (Engine::RaycastManager::GetInstance()->PickMeshWithMouse(a, p, Engine::EnemyManager::GetInstance()->enemymesh[0],
			*Engine::EnemyManager::GetInstance()->enemyTransform[0]))
		{
			cout << "D : " << a << " P : " << p.x << " " << p.y << " " << p.z << endl;

			for (int i = 0; i < 4; ++i)
			{
				
			}
		}

	if (DXUTWasKeyPressed('E'))
		Engine::ObjectManager::GetInstance()->AddObjectAtLayer<Missile>(L"테스트", L"테스트");

	GameObject::LateUpdate(dt);
}

void test::Render(const FLOAT& dt)
{
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	testdynamic->PlayAnimation(dt * 3);
	testshader->SetupTable();
	UINT pass = 0;
	LPD3DXEFFECT tempeffect = testshader->GetEffect();
	tempeffect->Begin(&pass, 0);
	tempeffect->BeginPass(0);
	testdynamic->RenderNoSkinnedMesh(tempeffect);
	tempeffect->EndPass();
	tempeffect->End();

	collider->RenderCollider();

	GameObject::Render(dt);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void test::Free(void)
{
	GameObject::Free();
}
