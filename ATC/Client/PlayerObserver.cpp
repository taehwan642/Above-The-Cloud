#include "DXUT.h"
#include "../Engine/Transform.h"
#include "../Engine/SubjectManager.h"
#include "../Client/MonsterBase.h"
#include "PlayerObserver.h"

void PlayerObserver::UpdateObserver(UINT _flag)
{
	void* data =  Engine::SubjectManager::GetInstance()->GetData(_flag);
	if (data == nullptr)
		return;
	switch (static_cast<PlayerInfos>(_flag))
	{
	case PlayerInfos::PLAYERTRANSFORM:
		playerTransform = reinterpret_cast<Engine::Transform*>(data);
		break;
	case PlayerInfos::PLAYERHEALTH:
		playerHealthpoint = *reinterpret_cast<INT*>(data);
		break;
	case PlayerInfos::PLAYERMISSILELOCKOBJECT:
		missileLock = reinterpret_cast<Engine::GameObject*>(data);
		break;
	default:
		break;
	}
}

void PlayerObserver::Free(void)
{

}
