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
	// ���ϴ� �±��� Transform���� list �޾ƿ���
	void AddMonsterData(MonsterType _type, MonsterBase* _transform);
	// Transform�� ���ϴ� �±��� list�� �ֱ�
	std::list<MonsterBase*> GetListWithMonsterType(MonsterType _type);
	
	void CheckMonsterDead(void);
	// �׾��� �� transform �����͸� ������. �׷��ٸ� Transform�� �ƴ� Monster�� �޾ƾ��ҵ�.

	void DeleteTransformDatas(void);

protected:

private:
	std::map<MonsterType, std::list<MonsterBase*>> monsterTransforms;
	// MonsterType���� ������
	// list�� �ִ´�.
	
};

