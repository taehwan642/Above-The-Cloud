#include "DXUT.h"
#include "../Engine/SubjectManager.h"
#include "PlayerObserver.h"
#include "../Engine/Transform.h"
#include "AimPoint.h"

AimPoint::AimPoint(wstring _texturetag) :
	Engine::DynamicUI(_texturetag)
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
	Engine::DynamicUI::Update(dt);
	D3DXVECTOR3 playerLook = -(*reinterpret_cast<D3DXVECTOR3*>(&playerTransform->worldMatrix._31));
	transform->position = playerTransform->position + playerLook * 3000;
	/*D3DXVECTOR3 pos = playerLook + D3DXVECTOR3(0, 0, 3);

	D3DXMATRIX			matView, matProj;
	D3DVIEWPORT9		ViewPort;
	D3DXVECTOR3			vScreenPos;
	DEVICE->GetViewport(&ViewPort);

	DEVICE->GetTransform(D3DTS_VIEW, &matView);
	DEVICE->GetTransform(D3DTS_PROJECTION, &matProj);
	D3DXVec3TransformCoord(&vScreenPos, &pos, &matView);
	D3DXVec3TransformCoord(&vScreenPos, &vScreenPos, &matProj);

	vScreenPos.x = (vScreenPos.x + 1) * ViewPort.Width / 2;
	vScreenPos.y = (-vScreenPos.y + 1) * ViewPort.Height / 2;

	transform->position = vScreenPos;*/
}

void AimPoint::LateUpdate(const FLOAT& dt)
{
	Engine::DynamicUI::LateUpdate(dt);
}

void AimPoint::Render(const FLOAT& dt)
{
	Engine::DynamicUI::Render(dt);
}

void AimPoint::Free(void)
{
	Engine::DynamicUI::Free();
}
