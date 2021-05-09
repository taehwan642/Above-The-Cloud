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
#include "MonsterBullet.h"
#include "BossDashGun.h"
#include "BossShootGun.h"
#include "MonsterInfoManager.h"
#include "CameraManager.h"
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
	transform->localPosition = { 0,0,-30 };
	observer = new PlayerObserver();
	Engine::SubjectManager::GetInstance()->Subscribe(observer);
	Engine::SubjectManager::GetInstance()->Notify(static_cast<UINT>(PlayerInfos::PLAYERTRANSFORM));

	collider = new Engine::Collider(6, &transform->localPosition);
	componentgroup.emplace(L"collider", collider);
	colliderdata.center = &transform->localPosition;
	colliderdata.radius = 6;
	colliderdata.tag = L"Monster";
	currentState = MONSTERIDLE;
	mesh->SetAnimationSet(currentState);

	Hp = 20;
	FullHP = 20;

	revolvePoint = new Engine::Transform(transform);
	componentgroup.emplace(L"revolvePoint", revolvePoint);

	// cos(0) = 1, sin(0) = 0
	theta[0] = 0;
	// cos(PI) = -1, sin(PI) = 0
	theta[1] = D3DX_PI;
	// cos(PI/2) = 0, sin(PI/2) = 1
	theta[2] = D3DX_PI / 2;
	// cos{(3*PI)/2} = 0, sin{(3*PI)/2} = -1
	theta[3] = -(D3DX_PI / 2);
}

Boss::~Boss(void)
{
}

void Boss::SetInformation(const D3DXVECTOR3& _position)
{
	MonsterBase::SetInformation(_position);
	
	for (int i = 0; i < 2; ++i)
	{
		bossDashGuns[i] = Engine::ObjectManager::GetInstance()->CheckActiveFalsedObjectAndSpawn<BossDashGun>(OBJ2, L"BossDashGun");
		bossDashGuns[i]->isAttatched = true;
		bossDashGuns[i]->SetInformation(transform->localPosition);
		bossShootGuns[i] = Engine::ObjectManager::GetInstance()->CheckActiveFalsedObjectAndSpawn<BossShootGun>(OBJ2, L"BossShootGun");
		bossShootGuns[i]->isAttatched = true;
		bossShootGuns[i]->SetInformation(transform->localPosition);
	}

	for (int i = 0; i < 4; ++i)
	{
		if (i < 2)
		{
			gunTransforms[i] = dynamic_cast<Engine::Transform*>(bossDashGuns[i]->GetComponent(L"Transform"));
			//gunTransforms[i]->AddReference();
		}
		else
		{
			gunTransforms[i] = dynamic_cast<Engine::Transform*>(bossShootGuns[i - 2]->GetComponent(L"Transform"));
			//gunTransforms[i]->AddReference();
		}
	}

	for (int i = 0; i < 4; ++i)
	{
		gunTransforms[i]->localPosition = transform->localPosition;
		memcpy(&gunTransforms[i]->worldMatrix._41, &transform->localPosition, sizeof(D3DXVECTOR3));
	}

	revolveLerpPoint = transform->localPosition;

	CameraManager::GetInstance()->SetCamera(CAM_CUTSCENE);
	CameraManager::GetInstance()->SetCurrentCutScene(CUTSCENE_BOSSSPAWN);

	Engine::CollisionManager::GetInstance()->PushData(MONSTER, this);
	MonsterInfoManager::GetInstance()->AddMonsterData(BOSS, this);
}

void Boss::Movement(const FLOAT& dt)
{
	movementspeed = 3.f;

	int s = rand() % 2;
	if (s == 0)
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
	else
	{
		int attrand = rand() % 2;
		if (attrand == 0)
		{
			for (int i = 0; i < 2; ++i)
			{
				movementqueue.emplace([=]() -> bool
					{
						revolvePoint->localPosition.z = 90.f;
						speed = defaultSpeed + 10;
						radius = defaultRadius - 20;
						delta += dt;
						if (delta > 1.5f)
						{
							delta = 0;
							return true;
						}
						return false;
					});
				movementqueue.emplace([=]()->bool
					{
						currentState = MONSTERSHOOT;
						mesh->SetAnimationSet(currentState);
						D3DXVECTOR3 dir = *reinterpret_cast<D3DXVECTOR3*>(&revolvePoint->worldMatrix._31);
						MonsterBullet* m = Engine::ObjectManager::GetInstance()->CheckActiveFalsedObjectAndSpawn<MonsterBullet>(OBJ2, L"MONSTERBULLET");
						D3DXVECTOR3 pos = revolvePoint->worldPosition;
						m->SetInformation(pos, dir, 2);
						return true;
					});
			}
			movementqueue.emplace([=]()->bool
				{
					revolvePoint->localPosition.z = 0;
					speed = defaultSpeed;
					radius = defaultRadius;
					movementspeed = 2.f;
					delta = 0;
					return true;
				});
		}
		else
		{
			for (int i = 0; i < 5; ++i)
			{
				movementqueue.emplace([=]()->bool
					{
						radius = 200.f;
						delta += dt;
						if (delta > 0.5f)
						{
							delta = 0;
							currentState = MONSTERSHOOT;
							mesh->SetAnimationSet(currentState);
							D3DXVECTOR3 dir = *reinterpret_cast<D3DXVECTOR3*>(&transform->worldMatrix._31);
							MonsterBullet* m = Engine::ObjectManager::GetInstance()->CheckActiveFalsedObjectAndSpawn<MonsterBullet>(OBJ2, L"MONSTERBULLET");
							m->SetInformation(transform->localPosition, dir);
							return true;
						}
						return false;
					});
			}
			movementqueue.emplace([=]()->bool
				{
					delta += dt;
					if (delta > 0.5f)
					{
						radius = defaultRadius;
						delta = 0;
						movementspeed = 2.f;
						return true;
					}
					return false;
				});
		}
		// animation on

	}
}

void Boss::DieAction(void)
{
	for (int i = 0; i < 2; ++i)
	{
		bossDashGuns[i]->isAttatched = false;
		bossDashGuns[i]->UnAttatch();
		bossShootGuns[i]->isAttatched = false;
		bossShootGuns[i]->UnAttatch();
	}
	
	CameraManager::GetInstance()->SetCamera(CAM_CUTSCENE);
	CameraManager::GetInstance()->SetCurrentCutScene(CUTSCENE_BOSSDEAD);
}

INT Boss::Update(const FLOAT& dt)
{
	MonsterBase::Update(dt);

	if (isActive == true && currentState != MONSTERDIE)
	{
		for (int i = 0; i < 4; ++i)
		{
			theta[i] += dt * speed;
		}

		for (int i = 0; i < 4; ++i)
		{
			D3DXVECTOR3 vec = {
				(radius * cos(theta[i])),
				(radius * sin(theta[i])),
				0 };
			D3DXVECTOR3 lerpvec;
			D3DXVec3TransformCoord(&lerpvec, &vec, &revolvePoint->worldMatrix);
			D3DXVec3Lerp(&gunTransforms[i]->localPosition, &gunTransforms[i]->localPosition, &lerpvec, dt * 5);
		}
	}

	

	//std::cout << t1->position.x << " " << t1->position.y << " " << t1->position.z << std::endl;
	
	return OBJALIVE;
}

void Boss::LateUpdate(const FLOAT& dt)
{
	//std::cout << "BOSS : " << transform->localPosition.x << " " << 
	//	transform->localPosition.y << " " << transform->localPosition.z << " " << std::endl;

	D3DXVECTOR3 look = observer->GetTransform()->localPosition - transform->localPosition;
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
	
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	MonsterBase::Render(dt);
}

void Boss::Free(void)
{
	Engine::SubjectManager::GetInstance()->UnSubscribe(observer);
	observer->Release();

	//for (int i = 0; i < 4; ++i)
		//Safe_Release(gunTransforms[i]);
	MonsterBase::Free();
}
