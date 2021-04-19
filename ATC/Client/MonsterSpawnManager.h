#pragma once
#include "../Engine/Singleton.h"
class PlayerObserver;
class MonsterSpawnManager final :
    public Engine::Singleton<MonsterSpawnManager>
{
private:
    PlayerObserver* observer = nullptr;
    std::map<Stage, std::list<std::pair<MonsterType, UINT>>> monsterSpawnDatas;
    D3DXVECTOR3 RandomPositionForMonster(void);
protected:
public:
    explicit MonsterSpawnManager(void);
    void AddSpawnData(const Stage& _stage, const MonsterType& _data, const UINT _monsterNum);
    void SpawnMonstersByData(const Stage& _stage);
    void DeleteDatas(void);
};
