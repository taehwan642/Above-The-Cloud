#pragma once
#include "../Engine/Singleton.h"
class MonsterSpawnManager final :
    public Engine::Singleton<MonsterSpawnManager>
{
private:
    std::vector<std::list<MonsterSpawnData>> monsterSpawnDatas;
protected:
public:
    void AddSpawnData(const Stage& _stage, const MonsterSpawnData& _data);
    void SpawnMonstersByData(const Stage& _stage);
};
