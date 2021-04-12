#include "DXUT.h"
#include "../Engine/Transform.h"
#include "../Engine/RenderManager.h"
#include "RadarPlane.h"

RadarPlane::RadarPlane(void) :
	StaticUI(L"RadarPlane")
{
	transform->localPosition = { 1150, 600 , 0};
}

RadarPlane::~RadarPlane(void)
{
}

INT RadarPlane::Update(const FLOAT& dt)
{
	POINT p;
	::GetCursorPos(&p);
	ScreenToClient(DXUTGetHWND(), &p);
	std::cout << p.x << " " << p.y << std::endl;
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
