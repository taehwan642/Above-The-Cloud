#include "DXUT.h"
#include "../Engine/SubjectManager.h"
#include "PlayerObserver.h"
#include "../Engine/Transform.h"
#include "AimPoint.h"

AimPoint::AimPoint(wstring _texturetag) :
	Engine::StaticUI(_texturetag)
{
	PlayerObserver* ob = new PlayerObserver();
	Engine::SubjectManager::GetInstance()->Subscribe(ob);
	Engine::SubjectManager::GetInstance()->Notify(static_cast<UINT>(PlayerInfos::PLAYERTRANSFORM));
	playerTransform = ob->GetTransform();
}

AimPoint::~AimPoint(void)
{
}

void AimPoint::Update(const FLOAT& dt)
{
	Engine::StaticUI::Update(dt);
	D3DXVECTOR3 playerLook = -(*reinterpret_cast<D3DXVECTOR3*>(&playerTransform->worldMatrix._31));
	D3DXVECTOR3 pos = playerTransform->position + playerLook * 4000;

	D3DXMATRIX			matView, matProj;
	D3DVIEWPORT9		viewPort;
	D3DXVECTOR3			screenPos;
	DEVICE->GetViewport(&viewPort);

	DEVICE->GetTransform(D3DTS_VIEW, &matView);
	DEVICE->GetTransform(D3DTS_PROJECTION, &matProj);
	D3DXVec3TransformCoord(&screenPos, &pos, &matView);
	D3DXVec3TransformCoord(&screenPos, &screenPos, &matProj);

	screenPos.x = (screenPos.x + 1) * viewPort.Width / 2;
	screenPos.y = (-screenPos.y + 1) * viewPort.Height / 2;

	transform->position = screenPos;
}

void AimPoint::LateUpdate(const FLOAT& dt)
{
	Engine::StaticUI::LateUpdate(dt);
}

void AimPoint::Render(const FLOAT& dt)
{
	Engine::StaticUI::Render(dt);
}

void AimPoint::Free(void)
{
	Engine::StaticUI::Free();
}
