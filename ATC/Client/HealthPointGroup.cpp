#include "DXUT.h"
#include "../Engine/SubjectManager.h"
#include "PlayerObserver.h"
#include "HealthPoint.h"
#include "HealthPointGroup.h"

HealthPointGroup::HealthPointGroup(void)
{
	for (int i = 0; i < 5; ++i)
	{
		hp[i] = new HealthPoint(L"Heart");
		hp[i]->SetPosition(D3DXVECTOR2(40 + (i * 60), 40));
	}
	observer = new PlayerObserver();
	Engine::SubjectManager::GetInstance()->Subscribe(observer);
	Engine::SubjectManager::GetInstance()->Notify(static_cast<UINT>(PlayerInfos::PLAYERHEALTH));
}

HealthPointGroup::~HealthPointGroup(void)
{
}

void HealthPointGroup::Update(const FLOAT& dt)
{

}

void HealthPointGroup::LateUpdate(const FLOAT& dt)
{
}

void HealthPointGroup::Render(const FLOAT& dt)
{
	for (int i = 0; i < observer->GetHealthPoint(); ++i)
		hp[i]->Render(dt);
}

void HealthPointGroup::Free(void)
{
	for (int i = 0; i < 5; ++i)
		hp[i]->Release();
	Engine::SubjectManager::GetInstance()->UnSubscribe(observer);
	observer->Release();
}
