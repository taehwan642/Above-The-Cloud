#include "DXUT.h"
#include "../Engine/Transform.h"
#include "MonsterBase.h"
#include "MonsterInfoManager.h"

void MonsterInfoManager::AddMonsterData(MonsterType _type, MonsterBase* _transform)
{
    auto& iter = monsterTransforms.find(_type);
    if (iter == monsterTransforms.end())
    {
        monsterTransforms[_type] = std::list<MonsterBase*>();
    }
    monsterTransforms[_type].emplace_back(_transform);
}

std::list<MonsterBase*> MonsterInfoManager::GetListWithMonsterType(MonsterType _type)
{
    return monsterTransforms[_type];
}

void MonsterInfoManager::CheckMonsterDead(void)
{
	for (auto& m : monsterTransforms)
	{
		auto& iter = m.second.begin();
		auto& iter_end = m.second.end();

		for (; iter != iter_end;)
		{
			if ((*iter)->GetActive() == false)
				iter = m.second.erase(iter);
			else
				++iter;
		}
	}
}

void MonsterInfoManager::DeleteTransformDatas(void)
{
    for (auto& it : monsterTransforms)
        it.second.clear();
    monsterTransforms.clear();
}
