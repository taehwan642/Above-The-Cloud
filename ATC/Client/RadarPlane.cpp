#include "DXUT.h"
#include "../Engine/Transform.h"
#include "../Engine/RenderManager.h"
#include "RadarDot.h"
#include "../Engine/ObjectManager.h"
#include "../Engine/SubjectManager.h"
#include "PlayerObserver.h"
#include "MonsterInfoManager.h"
#include "MonsterBase.h"
#include "RadarPlane.h"

// 스텐실 버퍼로 한번 해보기.

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

	
	for (int i = 0; i < MONSTEREND; ++i)
	{
		for (auto& v : MonsterInfoManager::GetInstance()->GetListWithMonsterType(static_cast<MonsterType>(i)))
		{
			D3DXVECTOR3 mpos = dynamic_cast<Engine::Transform*>(v->GetComponent(L"Transform"))->localPosition;
			//std::cout << "-POS : " << mpos.x << " " << mpos.y << " " << mpos.z << std::endl;
			D3DXVECTOR3 vec = observer->GetTransform()->localPosition - mpos;
			RadarDot* d = Engine::ObjectManager::GetInstance()->CheckActiveFalsedObjectAndSpawn<RadarDot>(UI, L"RadarDot");
			d->SetActive(true); // 구조 왜 이거 active false면 transform의 업데이트가 되지 않는지 확인해보기. 뭔가 꼬였다!!!
			dotpositions.emplace_back(d, vec);
		}
	}
	
	for (const auto& pos : dotpositions)
	{
		//std::cout << "RESULT : " <<  pos.second.x << " " << pos.second.z << std::endl;
		D3DXVECTOR3 result = { transform->localPosition.x + pos.second.x,
							   transform->localPosition.y + pos.second.z,
							   transform->localPosition.z };
		//std::cout << "REAL RESULT : " << result.x << " " << result.y << std::endl;
		pos.first->SetPosition(result);
	}

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
