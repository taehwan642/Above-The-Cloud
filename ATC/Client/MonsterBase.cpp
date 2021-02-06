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

void MonsterBase::CollisionEvent(const wstring& _objectTag, GameObject* _gameObject)
{
	if (_objectTag == L"Missile")
	{
		--Hp;
		_gameObject->SetActive(false);
	}
}

INT MonsterBase::Update(const FLOAT& dt)
{
	//if (Hp <= 0)
		//return OBJDEAD;

	if (!movementqueue.empty())
	{
		if (movementqueue.front()())
		{
			movementqueue.pop();
		}
	}
	Engine::GameObject::Update(dt);
	return OBJALIVE;
}

void MonsterBase::LateUpdate(const FLOAT& dt)
{
	if (movementspeed < 0)
		Movement(dt);
	else
		movementspeed -= dt;
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
