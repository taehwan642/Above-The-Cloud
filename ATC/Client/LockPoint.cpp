#include "DXUT.h"
#include "../Engine/Transform.h"
#include "PlayerObserver.h"
#include "../Engine/SubjectManager.h"
#include "../Engine/RenderManager.h"
#include "LockPoint.h"

LockPoint::LockPoint(void) :
	StaticUI(L"LockPoint")
{
	ob = new PlayerObserver();
	Engine::SubjectManager::GetInstance()->Subscribe(ob);
	Engine::SubjectManager::GetInstance()->Notify(static_cast<UINT>(PlayerInfos::PLAYERMISSILELOCKOBJECT));
	transform->position = { windowWidth / 2, windowHeight / 2, 0 };
}

LockPoint::~LockPoint(void)
{

}

INT LockPoint::Update(const FLOAT& dt)
{
	transform->rotation.z += 1.f * dt;
	Engine::StaticUI::Update(dt);
	Engine::RenderManager::GetInstance()->AddRenderObject(ID_UI, this);
	return OBJALIVE;
}

void LockPoint::LateUpdate(const FLOAT& dt)
{
	Engine::SubjectManager::GetInstance()->Notify(static_cast<UINT>(PlayerInfos::PLAYERMISSILELOCKOBJECT));
	if (ob->GetMissileLock() == nullptr || ob->GetMissileLock()->GetActive() == false)
	{
		transform->position = { 9999,9999,999 };
	}
	else
	{
		D3DXVECTOR3 screenpos = 
			dynamic_cast<Engine::Transform*>
			(ob->GetMissileLock()->GetComponent(L"Transform"))->position;

		D3DXMATRIX matView;
		DEVICE->GetTransform(D3DTS_VIEW, &matView);
		D3DXVec3TransformCoord(&screenpos, &screenpos, &matView);

		D3DXMATRIX matProj;
		DEVICE->GetTransform(D3DTS_PROJECTION, &matProj);
		D3DXVec3TransformCoord(&screenpos, &screenpos, &matProj);

		D3DVIEWPORT9 viewport;
		DEVICE->GetViewport(&viewport);

		screenpos.x = (screenpos.x + 1) * (viewport.Width * 0.5f);
		screenpos.y = (-screenpos.y + 1) * (viewport.Height * 0.5f);

		if (screenpos.z <= 1)
			transform->position = screenpos;
		else
			transform->position = { 9999,9999,999 };
	}

	Engine::StaticUI::LateUpdate(dt);
}

void LockPoint::Render(const FLOAT& dt)
{
	Engine::StaticUI::Render(dt);
}

void LockPoint::Free(void)
{
	Engine::SubjectManager::GetInstance()->UnSubscribe(ob);
	ob->Release();
	Engine::StaticUI::Free();
}
