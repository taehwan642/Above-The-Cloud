#include "DXUT.h"
#include "../Engine/SubjectManager.h"
#include "PlayerObserver.h"
#include "../Engine/Transform.h"
#include "../Engine/RenderManager.h"
#include "AimPoint.h"

AimPoint::AimPoint(std::wstring _texturetag) :
	Engine::StaticUI(_texturetag)
{
	ob = new PlayerObserver();
	Engine::SubjectManager::GetInstance()->Subscribe(ob);
	Engine::SubjectManager::GetInstance()->Notify(static_cast<UINT>(PlayerInfos::PLAYERTRANSFORM));
}

AimPoint::~AimPoint(void)
{
}

INT AimPoint::Update(const FLOAT& dt)
{
	Engine::StaticUI::Update(dt);
	D3DXVECTOR3 playerLook = -(*reinterpret_cast<D3DXVECTOR3*>(&ob->GetTransform()->worldMatrix._31));
	D3DXVECTOR3 pos = ob->GetTransform()->localPosition + playerLook * 5000;

	D3DXMATRIX			matView, matProj;
	D3DVIEWPORT9		viewPort;
	D3DXVECTOR3			screenPos;
	DEVICE->GetViewport(&viewPort);

	DEVICE->GetTransform(D3DTS_VIEW, &matView);
	DEVICE->GetTransform(D3DTS_PROJECTION, &matProj);
	D3DXVec3TransformCoord(&screenPos, &pos, &matView);
	D3DXVec3TransformCoord(&screenPos, &screenPos, &matProj);

	screenPos.x = (screenPos.x + 1) * (viewPort.Width / 2);

	screenPos.y = (-screenPos.y + 1) * (viewPort.Height / 2);

	transform->localPosition = screenPos;
	if (pointlock == true)
	{
		POINT p;
		p.x = transform->localPosition.x;
		p.y = transform->localPosition.y;
		ClientToScreen(DXUTGetHWND(), &p);
		::SetCursorPos(p.x, p.y);
	}
	Engine::RenderManager::GetInstance()->AddRenderObject(ID_UI, this);
	return OBJALIVE;
}

void AimPoint::LateUpdate(const FLOAT& dt)
{
	if (DXUTWasKeyPressed('C'))
		lookback = !lookback;
	if (DXUTWasKeyPressed(VK_F1))
		pointlock = !pointlock;
	Engine::StaticUI::LateUpdate(dt);
}

void AimPoint::Render(const FLOAT& dt)
{
	if (!lookback)
		Engine::StaticUI::Render(dt);
}

void AimPoint::Free(void)
{
	Engine::SubjectManager::GetInstance()->UnSubscribe(ob);
	ob->Release();
	Engine::StaticUI::Free();
}
