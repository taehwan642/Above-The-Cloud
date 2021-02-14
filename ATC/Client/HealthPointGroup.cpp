#include "DXUT.h"
#include "../Engine/SubjectManager.h"
#include "PlayerObserver.h"
#include "HealthPoint.h"
#include "../Engine/RenderManager.h"
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

INT HealthPointGroup::Update(const FLOAT& dt)
{
	for (int i = 0; i < observer->GetHealthPoint(); ++i)
		Engine::RenderManager::GetInstance()->AddRenderObject(ID_UI, hp[i]);
	return OBJALIVE;
}

void HealthPointGroup::LateUpdate(const FLOAT& dt)
{
}

void HealthPointGroup::Render(const FLOAT& dt)
{
	
}

void HealthPointGroup::Free(void)
{
	for (int i = 0; i < 5; ++i)
		hp[i]->Release();
	Engine::SubjectManager::GetInstance()->UnSubscribe(observer);
	observer->Release();
}
