#include "DXUT.h"
#include "../Engine/Transform.h"
#include "../Engine/Texture.h"
#include "../Engine/SubjectManager.h"
#include "PlayerObserver.h"
#include "PlaneShadow.h"

PlaneShadow::PlaneShadow(void)
{
	observer = new PlayerObserver();
	Engine::SubjectManager::GetInstance()->UnSubscribe(observer);
	Engine::SubjectManager::GetInstance()->Notify(static_cast<UINT>(PlayerInfos::PLAYERTRANSFORM));
	Engine::SubjectManager::GetInstance()->Notify(static_cast<UINT>(PlayerInfos::PLAYERDEAD));
}

PlaneShadow::~PlaneShadow(void)
{
}

INT PlaneShadow::Update(const FLOAT& dt)
{
	DynamicUI::Update(dt);
	return OBJALIVE;
}

void PlaneShadow::LateUpdate(const FLOAT& dt)
{
	DynamicUI::LateUpdate(dt);
}

void PlaneShadow::Render(const FLOAT& dt)
{
	if (observer->GetIsPlayerDead() == true)
		return;
	DynamicUI::Render(dt);
}

void PlaneShadow::Free(void)
{
	DynamicUI::Free();
}
