#include "DXUT.h"
#include "../Engine/ObjectManager.h"
#include "Monster1.h"
#include "Monster2.h"
#include "MonsterSpawnManager.h"
void MonsterSpawnManager::AddSpawnData(const Stage& _stage, const MonsterSpawnData& _data)
{
	monsterSpawnDatas[_stage].emplace_back(_data);
}

void MonsterSpawnManager::SpawnMonstersByData(const Stage& _stage)
{
	for (auto& iter : monsterSpawnDatas[_stage])
	{
		std::list<MonsterSpawnData>::const_iterator iterator = monsterSpawnDatas[_stage].begin();
		std::list<MonsterSpawnData>::const_iterator iterend = monsterSpawnDatas[_stage].end();
		
		for (; iterator != iterend;)
		{
			// Spawn
			switch ((*iterator).type)
			{
			case MONSTER1:
			{
				Monster1* monster1 = Engine::ObjectManager::GetInstance()->GetActiveFalsedObject<Monster1>(L"", L"");
				if (monster1 == nullptr)
				{
					monster1 = Engine::ObjectManager::GetInstance()->AddObjectAtLayer<Monster1>(L"", L"");
				}
				else
					monster1->SetActive(true);
				break;
			}
			case MONSTER2:
			{
				Monster2* monster2 = Engine::ObjectManager::GetInstance()->GetActiveFalsedObject<Monster2>(L"", L"");
				if (monster2 == nullptr)
				{
					monster2 = Engine::ObjectManager::GetInstance()->AddObjectAtLayer<Monster2>(L"", L"");
				}
				else
					monster2->SetActive(true);
				break;
			}
			case BOSS:
			{
				break;
			}
			default:
				break;
			}
			++iterator;
		}
	}
}
