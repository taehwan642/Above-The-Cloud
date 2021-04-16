#include "DXUT.h"
#include "../Engine/Transform.h"
#include "../Engine/RenderManager.h"
#include "RadarDot.h"

void RadarDot::SetPosition(const D3DXVECTOR3& _position)
{
    transform->localPosition = _position;
}

RadarDot::RadarDot(void) :
    StaticUI(L"RadarDot")
{
    transform->localPosition = { 255, 255, 0 };
    transform->scale = { 0.05f, 0.05f, 0.05f };
}

RadarDot::~RadarDot(void)
{

}

INT RadarDot::Update(const FLOAT& dt)
{
    Engine::RenderManager::GetInstance()->AddRenderObject(ID_UI, this);
    return StaticUI::Update(dt);
}

void RadarDot::LateUpdate(const FLOAT& dt)
{
    StaticUI::LateUpdate(dt);
}

void RadarDot::Render(const FLOAT& dt)
{
    StaticUI::Render(dt);
}

void RadarDot::Free(void)
{
    StaticUI::Free();
}
