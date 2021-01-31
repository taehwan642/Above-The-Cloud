#include "DXUT.h"
#include "../Engine/Transform.h"
#include "PlayerObserver.h"
#include "../Engine/SubjectManager.h"
#include "LockPoint.h"

LockPoint::LockPoint(void) :
	StaticUI(L"LockPoint")
{
	ob = new PlayerObserver();
	Engine::SubjectManager::GetInstance()->Subscribe(ob);
	Engine::SubjectManager::GetInstance()->Notify(static_cast<UINT>(PlayerInfos::PLAYERMISSILELOCKOBJECT));
	transform->position = { windowWidth / 2, windowHeight / 2 ,0 };
}

LockPoint::~LockPoint(void)
{
}

void LockPoint::Update(const FLOAT& dt)
{
	transform->rotation.z += 1.f * dt;
	Engine::StaticUI::Update(dt);
}

void LockPoint::LateUpdate(const FLOAT& dt)
{
	Engine::StaticUI::LateUpdate(dt);
}

void LockPoint::Render(const FLOAT& dt)
{
	Engine::StaticUI::Render(dt);
}

void LockPoint::Free(void)
{
	Engine::StaticUI::Free();
}
