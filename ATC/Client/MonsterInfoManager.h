#pragma once
#include "../Engine/Singleton.h"
NAMESPACE(Engine)
class Transform;
END

class MonsterInfoManager final :
	public Engine::Singleton<MonsterInfoManager>
{
public:
	// 원하는 태그의 Transform들의 list 받아오기
	// Transform을 원하는 태그의 list에 넣기

protected:

private:
	std::map<MonsterType, std::list<Engine::Transform*>> monsterTransforms;
	// MonsterType으로 나눠서
	// list에 넣는다.
	
};

