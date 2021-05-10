#include "DXUT.h"
#include "../Engine/ObjectManager.h"
#include "Monster1.h"
#include "Monster2.h"
#include "../Engine/SubjectManager.h"
#include "PlayerObserver.h"
#include "../Engine/Transform.h"
#include "Boss.h"
#include "BossDashGun.h"
#include "BossShootGun.h"
#include "MonsterSpawnManager.h"

D3DXVECTOR3 MonsterSpawnManager::RandomPositionForMonster(void)
{
	INT r;
	FLOAT rx = static_cast<float>((rand() % 10)) / 10;
	r = rand() % 2;
	r == 0 ? rx *= -1 : 0;
	FLOAT ry = static_cast<float>((rand() % 10)) / 10;
	FLOAT rz = static_cast<float>((rand() % 10)) / 10;
	r = rand() % 2;
	r == 0 ? rz *= -1 : 0;
	D3DXVECTOR3 randomPosition = { rx, ry, rz };
	D3DXVec3Normalize(&randomPosition, &randomPosition);
	randomPosition *= 100;
	return randomPosition;
}

MonsterSpawnManager::MonsterSpawnManager()
{
	observer = new PlayerObserver();
	Engine::SubjectManager::GetInstance()->Subscribe(observer);
	Engine::SubjectManager::GetInstance()->Notify(static_cast<UINT>(PlayerInfos::PLAYERTRANSFORM));
}

void MonsterSpawnManager::AddSpawnData(const Stage& _stage, const MonsterType& _data, const UINT _monsterNum)
{
	auto& iter = monsterSpawnDatas.find(_stage);
	if (iter == monsterSpawnDatas.end())
		monsterSpawnDatas[_stage] = std::list<std::pair<MonsterType, UINT>>();

	monsterSpawnDatas[_stage].emplace_back(_data, _monsterNum);
}

void MonsterSpawnManager::SpawnMonstersByData(const Stage& _stage)
{
	std::cout << static_cast<int>(_stage) << std::endl;
	for (const auto& iter : monsterSpawnDatas[_stage])
	{
		switch (iter.first)
		{
		case MONSTER1:
		{
			for (int i = 0; i < iter.second; ++i)
			{
				Monster1* monster1 = Engine::ObjectManager::GetInstance()->CheckActiveFalsedObjectAndSpawn<Monster1>(OBJ2, L"Monster1");
				monster1->SetInformation(RandomPositionForMonster());
			}
			break;
		}
		case MONSTER2:
		{
			for (int i = 0; i < iter.second; ++i)
			{
				Monster2* monster2 = Engine::ObjectManager::GetInstance()->CheckActiveFalsedObjectAndSpawn<Monster2>(OBJ2, L"Monster2");
				monster2->SetInformation(RandomPositionForMonster());
			}
			break;
		}
		case BOSS:
		{
			for (int i = 0; i < iter.second; ++i)
			{
				Boss* boss = Engine::ObjectManager::GetInstance()->CheckActiveFalsedObjectAndSpawn<Boss>(OBJ2, L"Boss");
				boss->SetInformation(RandomPositionForMonster());
			}
			break;
		}
		case BOSSDASHGUN:
		{
			for (int i = 0; i < iter.second; ++i)
			{
			}
			break;
		}
		case BOSSSHOOTGUN:
		{
			for (int i = 0; i < iter.second; ++i)
			{
			}
			break;
		}
		default:
			break;
		}
	}
}

void MonsterSpawnManager::DeleteDatas(void)
{
	Engine::SubjectManager::GetInstance()->UnSubscribe(observer);
	Safe_Delete(observer);
	for (auto& iter : monsterSpawnDatas)
		iter.second.clear();
	monsterSpawnDatas.clear();
}
