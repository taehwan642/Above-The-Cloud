#include "DXUT.h"
#include "../Engine/Transform.h"
#include "MonsterInfoManager.h"

void MonsterInfoManager::AddTransformData(MonsterType _type, Engine::Transform* _transform)
{
    auto& iter = monsterTransforms.find(_type);
    if (iter == monsterTransforms.end())
    {
        monsterTransforms[_type] = std::list<Engine::Transform*>();
    }
    monsterTransforms[_type].emplace_back(_transform);
}

std::list<Engine::Transform*> MonsterInfoManager::GetListWithMonsterType(MonsterType _type)
{
    return monsterTransforms[_type];
}

void MonsterInfoManager::DeleteTransformDatas(void)
{
    for (auto& it : monsterTransforms)
        it.second.clear();
    monsterTransforms.clear();
}
