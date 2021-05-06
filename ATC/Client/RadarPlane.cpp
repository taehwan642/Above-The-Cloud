#include "DXUT.h"
#include "../Engine/Transform.h"
#include "../Engine/RenderManager.h"
#include "RadarDot.h"
#include "../Engine/ObjectManager.h"
#include "../Engine/SubjectManager.h"
#include "PlayerObserver.h"
#include "RadarPlane.h"

RadarPlane::RadarPlane(void) :
	StaticUI(L"RadarPlane")
{
	transform->localPosition = { 1150, 600 , 0 };
	middledot = Engine::ObjectManager::GetInstance()->CheckActiveFalsedObjectAndSpawn<RadarDot>(UI, L"RadarDot");
	middledot->SetPosition(transform->localPosition);

	observer = new PlayerObserver();
	Engine::SubjectManager::GetInstance()->Subscribe(observer);
	Engine::SubjectManager::GetInstance()->Notify(static_cast<UINT>(PlayerInfos::PLAYERTRANSFORM));
}

RadarPlane::~RadarPlane(void)
{
}

INT RadarPlane::Update(const FLOAT& dt)
{
	for (auto& const v : dotpositions)
		v.first->SetActive(false);
	dotpositions.clear();

	D3DXVECTOR3 vec = observer->GetTransform()->localPosition - testPosition;
	
	dotpositions.emplace_back(
		Engine::ObjectManager::GetInstance()->CheckActiveFalsedObjectAndSpawn<RadarDot>(UI, L"RadarDot"),
		std::move(vec));
	
	for (const auto& pos : dotpositions)
		pos.first->SetPosition(D3DXVECTOR3(
			transform->localPosition.x + pos.second.x, 
			transform->localPosition.y + pos.second.z, 
			transform->localPosition.z));
	
	Engine::RenderManager::GetInstance()->AddRenderObject(ID_UI, this);
	return StaticUI::Update(dt);
}

void RadarPlane::LateUpdate(const FLOAT& dt)
{
	StaticUI::LateUpdate(dt);
}

void RadarPlane::Render(const FLOAT& dt)
{
	StaticUI::Render(dt);
}

void RadarPlane::Free(void)
{
	for (int i = 0; i < dotpositions.size(); ++i)
		dotpositions.at(i).first->Release();
	Engine::SubjectManager::GetInstance()->UnSubscribe(observer);
	observer->Release();
	StaticUI::Free();
}
