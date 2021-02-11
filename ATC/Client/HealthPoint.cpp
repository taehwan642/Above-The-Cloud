#include "DXUT.h"
#include "../Engine/Transform.h"
#include "HealthPoint.h"

HealthPoint::HealthPoint(std::wstring _texturetag) :
	Engine::StaticUI(_texturetag)
{
	transform->position.x = 30;
	transform->position.y = 30;
	transform->scale = { 0.2f, 0.2f, 0.2f };
}

HealthPoint::~HealthPoint(void)
{
}

INT HealthPoint::Update(const FLOAT& dt)
{
	Engine::StaticUI::Update(dt);
	return OBJALIVE;
}

void HealthPoint::LateUpdate(const FLOAT& dt)
{
	Engine::StaticUI::LateUpdate(dt);
}

void HealthPoint::Render(const FLOAT& dt)
{
	Engine::StaticUI::Render(dt);
}

void HealthPoint::Free(void)
{
	Engine::StaticUI::Free();
}
