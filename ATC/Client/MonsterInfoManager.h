#pragma once
#include "../Engine/Singleton.h"
NAMESPACE(Engine)
class Transform;
END
class MonsterBase;

class MonsterInfoManager final :
	public Engine::Singleton<MonsterInfoManager>
{
public:
	// 원하는 태그의 Transform들의 list 받아오기
	void AddMonsterData(MonsterType _type, MonsterBase* _transform);
	// Transform을 원하는 태그의 list에 넣기
	std::list<MonsterBase*> GetListWithMonsterType(MonsterType _type);
	
	void CheckMonsterDead(void);
	// 죽었을 때 transform 데이터를 빼야함. 그렇다면 Transform이 아닌 Monster를 받아야할듯.

	void DeleteTransformDatas(void);

protected:

private:
	std::map<MonsterType, std::list<MonsterBase*>> monsterTransforms;
	// MonsterType으로 나눠서
	// list에 넣는다.
	
};

