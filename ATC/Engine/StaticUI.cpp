#include "DXUT.h"
#include "Transform.h"
#include "GraphicsManager.h"
#include "Texture.h"
#include "StaticUI.h"
USING(Engine)

StaticUI::StaticUI(void)
{
}

StaticUI::StaticUI(std::wstring _texturetag)
{
	UIBase::SetInformation(_texturetag);
}

StaticUI::StaticUI(std::wstring _texturetag, Transform* _parent)
{
	UIBase::SetInformation(_texturetag, _parent);
}

StaticUI::~StaticUI(void)
{
}

void StaticUI::SetPosition(const D3DXVECTOR2& _position)
{
	transform->position.x = _position.x;
	transform->position.y = _position.y;
}

INT StaticUI::Update(const FLOAT& dt)
{
	UIBase::Update(dt);
	return OBJALIVE;
}

void StaticUI::LateUpdate(const FLOAT& dt)
{
	UIBase::LateUpdate(dt);
}

void StaticUI::Render(const FLOAT& dt)
{
	D3DXMATRIX m;
	D3DXMatrixTransformation2D(&m, nullptr, 0,
		&D3DXVECTOR2(transform->scale.x, transform->scale.y),
		nullptr, transform->rotation.z,
		&D3DXVECTOR2(transform->position.x, transform->position.y));
	GraphicsManager::GetInstance()->GetSprite()->SetTransform(&m);
	GraphicsManager::GetInstance()->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);

	LPDIRECT3DTEXTURE9 uiTexture = texture->GetTextureByIndex(currentTextureindex);
	if (uiTexture == nullptr)
		return;
	D3DSURFACE_DESC desc;
	uiTexture->GetLevelDesc(0, &desc);
	D3DXVECTOR3 center = { pivot.x * desc.Width, pivot.y * desc.Height, 0 };
	GraphicsManager::GetInstance()->GetSprite()->Draw(texture->GetTextureByIndex(currentTextureindex),
		NULL, &center, NULL, D3DCOLOR_RGBA(255, 255, 255, 255));
	GraphicsManager::GetInstance()->GetSprite()->End();
	UIBase::Render(dt);
}

void StaticUI::Free(void)
{
	UIBase::Free();
}
