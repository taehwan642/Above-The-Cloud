#include "DXUT.h"
#include "Transform.h"
#include "RaycastManager.h"
#include "RenderManager.h"
#include "Texture.h"
#include "Button.h"

USING(Engine)
Button::Button(const std::wstring& _texturetag, const D3DXVECTOR3& _position)
{
	UIBase::SetInformation(_texturetag);
	transform->localPosition = _position;
	transform->scale = { 0.5f,0.5f,0.5f };
}

Button::~Button(void)
{
}

INT Button::Update(const FLOAT& dt)
{
	DynamicUI::Update(dt);
	RenderManager::GetInstance()->AddRenderObject(ID_UI, this);
	return OBJALIVE;
}

void Button::LateUpdate(const FLOAT& dt)
{
	DynamicUI::LateUpdate(dt);
}

void Button::Render(const FLOAT& dt)
{
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	DEVICE->SetRenderState(D3DRS_ALPHAREF, 0x00000088);

	DynamicUI::Render(dt);
	texture->RenderTexture(DynamicUI::currentTextureindex);
	DynamicUI::RenderBuffer();

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

bool Button::IsMouseOn(void)
{
	bool isPicked = false;
	INDEX16* index = nullptr;
	VTXTEX* vertex = nullptr;

	vb->Lock(0, 0, reinterpret_cast<void**>(&vertex), 0);
	ib->Lock(0, 0, reinterpret_cast<void**>(&index), 0);

	for (DWORD i = 0; i < tricnt; ++i)
	{
		D3DXVECTOR3 p0 = vertex[index[i]._0].pos;
		D3DXVECTOR3 p1 = vertex[index[i]._1].pos;
		D3DXVECTOR3 p2 = vertex[index[i]._2].pos;
		FLOAT dist;
		D3DXVECTOR3 pos;
		if (RaycastManager::GetInstance()->PickTriWithMouse(dist, pos, p0, p1, p2, transform->worldMatrix))
		{
			isPicked = true;
			break;
		}
	}

	vb->Unlock();
	ib->Unlock();

	return isPicked;
}

void Button::SetButtonFunction(std::function<void(void)> _function)
{
	buttonFunction = _function;
}

std::function<void(void)> Button::GetButtonFunction(void) const
{
	return buttonFunction;
}

void Button::Free(void)
{
	DynamicUI::Free();
}
