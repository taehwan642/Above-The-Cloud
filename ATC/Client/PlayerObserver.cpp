#include "DXUT.h"
#include "../Engine/Transform.h"
#include "../Engine/SubjectManager.h"
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
	default:
		break;
	}
}
