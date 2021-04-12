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


// �ʿ� �ִ� ��� ������ ��ġ�� �߿�, distance�� 50 �̳��� �ֵ鸸 ���� ����.
// ��� ��, ���� �÷��̾���� dist�� ���ؼ� �� RadarPlane���� dist���� ������ ���� +���� RadarDot�� ���� �ɵ�.

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
