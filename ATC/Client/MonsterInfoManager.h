#pragma once
#include "../Engine/Singleton.h"
NAMESPACE(Engine)
class Transform;
END

class MonsterInfoManager final :
	public Engine::Singleton<MonsterInfoManager>
{
public:
	// ���ϴ� �±��� Transform���� list �޾ƿ���
	void AddTransformData(MonsterType _type, Engine::Transform* _transform);
	// Transform�� ���ϴ� �±��� list�� �ֱ�
	std::list<Engine::Transform*> GetListWithMonsterType(MonsterType _type);

protected:

private:
	std::map<MonsterType, std::list<Engine::Transform*>> monsterTransforms;
	// MonsterType���� ������
	// list�� �ִ´�.
	
};

