#include "DXUT.h"
#include "../Engine/Transform.h"
#include "../Engine/RenderManager.h"
#include "RadarDot.h"
#include "../Engine/ObjectManager.h"
#include "RadarPlane.h"

RadarPlane::RadarPlane(void) :
	StaticUI(L"RadarPlane")
{
	transform->localPosition = { 1150, 600 , 0};
	RadarDot* dot = Engine::ObjectManager::GetInstance()->CheckActiveFalsedObjectAndSpawn<RadarDot>(UI, L"RADARDOT");
	dot->SetPosition(transform->localPosition);
}

RadarPlane::~RadarPlane(void)
{
}


// 맵에 있는 모든 적들의 위치들 중에, distance가 50 이내인 애들만 띄우기 시작.
// 띄울 때, 적과 플레이어와의 dist만 구해서 그 RadarPlane에서 dist에서 조정한 값을 +해준 RadarDot를 띄우면 될듯.

INT RadarPlane::Update(const FLOAT& dt)
{
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
	StaticUI::Free();
}
