#include "DXUT.h"
#include "../Engine/ObjectManager.h"
#include "Monster1.h"
#include "Monster2.h"
#include "../Engine/SubjectManager.h"
#include "PlayerObserver.h"
#include "../Engine/Transform.h"
#include "MonsterSpawnManager.h"

D3DXVECTOR3 MonsterSpawnManager::RandomPositionForMonster(void)
{
	float rx = static_cast<float>((rand() % 10)) / 10;
	float ry = static_cast<float>((rand() % 10)) / 10;
	float rz = static_cast<float>((rand() % 10)) / 10;
	D3DXVECTOR3 randomPosition = { rx,ry,rz };
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
	for (auto& iter : monsterSpawnDatas[_stage])
	{
		std::list<std::pair<MonsterType, UINT>>::const_iterator iterator = monsterSpawnDatas[_stage].begin();
		std::list<std::pair<MonsterType, UINT>>::const_iterator iterend = monsterSpawnDatas[_stage].end();
		
		for (; iterator != iterend;)
		{
			switch ((*iterator).first)
			{
			case MONSTER1:
			{
				for (int i = 0; i < (*iterator).second; ++i)
				{
					Monster1* monster1 = Engine::ObjectManager::GetInstance()->GetActiveFalsedObject<Monster1>(OBJ2, L"Monster1");
					if (monster1 == nullptr)
					{
						monster1 = Engine::ObjectManager::GetInstance()->AddObjectAtLayer<Monster1>(OBJ2, L"Monster1");
						monster1->SetInformation(RandomPositionForMonster());
					}
					else
						monster1->SetInformation(RandomPositionForMonster());
				}
				break;
			}
			case MONSTER2:
			{
				for (int i = 0; i < (*iterator).second; ++i)
				{
					Monster2* monster2 = Engine::ObjectManager::GetInstance()->GetActiveFalsedObject<Monster2>(OBJ2, L"Monster2");
					if (monster2 == nullptr)
					{
						monster2 = Engine::ObjectManager::GetInstance()->AddObjectAtLayer<Monster2>(OBJ2, L"Monster2");
						monster2->SetInformation(RandomPositionForMonster());
					}
					else
						monster2->SetInformation(RandomPositionForMonster());
				}
				break;
			}
			case BOSS:
			{
				for (int i = 0; i < (*iterator).second; ++i)
				{
				}
				break;
			}
			default:
				break;
			}
			++iterator;
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
