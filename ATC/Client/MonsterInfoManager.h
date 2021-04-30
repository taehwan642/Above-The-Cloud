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
	// Transform�� ���ϴ� �±��� list�� �ֱ�

protected:

private:
	std::map<MonsterType, std::list<Engine::Transform*>> monsterTransforms;
	// MonsterType���� ������
	// list�� �ִ´�.
	
};

