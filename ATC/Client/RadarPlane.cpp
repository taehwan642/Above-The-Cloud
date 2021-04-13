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
	transform->localPosition = { 1150, 600 , 0};
	RadarDot* dot = Engine::ObjectManager::GetInstance()->CheckActiveFalsedObjectAndSpawn<RadarDot>(UI, L"RADARDOT");
	dot->SetPosition(transform->localPosition);

	observer = new PlayerObserver();
	Engine::SubjectManager::GetInstance()->Subscribe(observer);
	Engine::SubjectManager::GetInstance()->Notify(static_cast<UINT>(PlayerInfos::PLAYERTRANSFORM));
}

RadarPlane::~RadarPlane(void)
{
}

// �ʿ� �ִ� ��� ������ ��ġ�� �߿�, distance�� 50 �̳��� �ֵ鸸 ���� ����.
// ��� ��, ���� �÷��̾���� dist�� ���ؼ� �� RadarPlane���� dist���� ������ ���� +���� RadarDot�� ���� �ɵ�.

INT RadarPlane::Update(const FLOAT& dt)
{
	D3DXVECTOR3 vec = testPosition - observer->GetTransform()->localPosition;
	if (D3DXVec3LengthSq(&vec) < 250)
	{
		dotpositions.emplace_back(std::move(vec));
	}

	Engine::RenderManager::GetInstance()->AddRenderObject(ID_UI, this);
	return StaticUI::Update(dt);
}

void RadarPlane::LateUpdate(const FLOAT& dt)
{
	for (const auto& pos : dotpositions)
	{
				
	}

	StaticUI::LateUpdate(dt);
}

void RadarPlane::Render(const FLOAT& dt)
{
	StaticUI::Render(dt);
}

void RadarPlane::Free(void)
{
	StaticUI::Free();
}
