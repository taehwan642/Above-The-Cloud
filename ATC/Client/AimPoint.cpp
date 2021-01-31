#include "DXUT.h"
#include "../Engine/SubjectManager.h"
#include "PlayerObserver.h"
#include "Camera.h"
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
	D3DXVECTOR3 pos = playerTransform->position + playerLook * 5000;

	D3DXMATRIX			matView, matProj;
	D3DVIEWPORT9		viewPort;
	D3DXVECTOR3			screenPos;
	DEVICE->GetViewport(&viewPort);

	DEVICE->GetTransform(D3DTS_VIEW, &matView);
	DEVICE->GetTransform(D3DTS_PROJECTION, &matProj);
	D3DXVec3TransformCoord(&screenPos, &pos, &matView);
	D3DXVec3TransformCoord(&screenPos, &screenPos, &matProj);

	// 스크린 좌표 최상단이 <0, 0> 이니까 x에 + 1을 해야 계산이 된다.
	screenPos.x = (screenPos.x + 1) * (viewPort.Width / 2);

	// 스크린 좌표는 +로 갈수록 밑으로 가며, 
	// y는 +로 갈수록 위로 가기에 스크린 좌표에 맞추기 위해서 + 1을 해준다.
	// 스크린 좌표는 왼쪽 최상단이 <0, 0> 이기에 -인 Screenpos에 + 1을 해줘서 중간을 맞춰야한다
	screenPos.y = (-screenPos.y + 1) * (viewPort.Height / 2);

	// 최종적으로, 정규좌표의 왼쪽 최상단은 -1, 1이고 스크린좌표의 왼쪽 최상단은 0, 0이기에
	// 정규좌표에서 스크린좌표로 변환하기 위하여 -1에는 +1을 하여 0, 1에는 -1을 하여 0을 맞춘다.
	// 뒤에 뷰포트 / 2 를 곱하는 이유는 중간에 위치한 좌표는 0, 0 이기에 그렇게 한다.

	transform->position = screenPos;
	if (pointlock == true)
	{
		POINT p;
		p.x = transform->position.x;
		p.y = transform->position.y;
		ClientToScreen(DXUTGetHWND(), &p);
		::SetCursorPos(p.x, p.y);
	}
	
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
	Engine::StaticUI::Free();
}
