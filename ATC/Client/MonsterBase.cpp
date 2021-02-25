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
#include "../Engine/RenderManager.h"
#include "../Engine/ObjectManager.h"
#include "../Engine/TextureEffect.h"
#include "MonsterBase.h"

MonsterBase::MonsterBase(void)
{
}

MonsterBase::~MonsterBase(void)
{
}

void MonsterBase::GetHit(const FLOAT& _damageamount)
{
	Hp -= _damageamount;
}

void MonsterBase::SetInformation(const D3DXVECTOR3& _position)
{
	transform->position = _position;
	Hp = FullHP;
	currentState = MONSTERIDLE;
	mesh->SetAnimationSet(currentState);
	isActive = true;
	Engine::CollisionManager::GetInstance()->PushData(MONSTER, this);
}

void MonsterBase::CollisionEvent(const std::wstring& _objectTag, GameObject* _gameObject)
{
	if (_objectTag == L"Missile" || _objectTag == L"PlayerShoot")
	{
		--Hp;
	}
}

INT MonsterBase::Update(const FLOAT& dt)
{
	Engine::GameObject::Update(dt);
	if (isActive)
		Engine::RenderManager::GetInstance()->AddRenderObject(ID_NORMALMESH, this);
	return OBJALIVE;
}

void MonsterBase::LateUpdate(const FLOAT& dt)
{
	if (movementspeed < 0)
		Movement(dt);
	else
		movementspeed -= dt;

	if (!movementqueue.empty())
	{
		if (currentState != MONSTERDIE && movementqueue.front()())
		{
			movementqueue.pop();
		}
	}

	if (Hp <= 0)
	{
		currentState = MONSTERDIE;
		mesh->SetAnimationSet(currentState);
	}

	if (currentState == MONSTERSHOOT)
	{
		if (mesh->GetIsAnimationEnd() == true)
		{
			currentState = MONSTERIDLE;
			mesh->SetAnimationSet(currentState);
		}
	}
	else if (currentState == MONSTERDIE)
	{
		transform->position.y -= 30 * dt;
		if (transform->position.y <= -50)
		{
			for (int i = 0; i < 1; ++i)
			{
				Engine::TextureEffect* t =
					Engine::ObjectManager::GetInstance()->CheckActiveFalsedObjectAndSpawn<Engine::TextureEffect>(EFFECT, L"Effect");
				t->SetInformation(L"Explosion",
					{ transform->position.x, -45, transform->position.z },
					{ 5,5,5 }, nullptr, 0.05f);
			}

			isActive = false;
		}
	}

	Engine::GameObject::LateUpdate(dt);
}

void MonsterBase::Render(const FLOAT& dt)
{
	Engine::GameObject::Render(dt);
}

void MonsterBase::Free(void)
{
	Engine::GameObject::Free();
}
