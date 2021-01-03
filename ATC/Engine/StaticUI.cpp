#include "DXUT.h"
#include "Transform.h"
#include "GraphicsManager.h"
#include "Texture.h"
#include "StaticUI.h"
USING(Engine)

StaticUI::StaticUI(void)
{
}

StaticUI::StaticUI(wstring _texturetag) :
	UIBase(_texturetag)
{
}

StaticUI::~StaticUI(void)
{
}

void StaticUI::SetPosition(const D3DXVECTOR2& _position)
{
	transform->position.x = _position.x;
	transform->position.y = _position.y;
}

void StaticUI::Update(const FLOAT& dt)
{
	GameObject::Update(dt);
}

void StaticUI::LateUpdate(const FLOAT& dt)
{
	GameObject::LateUpdate(dt);
}

void StaticUI::Render(const FLOAT& dt)
{
	D3DXMATRIX m;
	D3DXMatrixTransformation2D(&m, nullptr, 0,
		&D3DXVECTOR2(transform->scale.x, transform->scale.y),
		nullptr, 0,
		&D3DXVECTOR2(transform->position.x, transform->position.y));
	GraphicsManager::GetInstance()->GetSprite()->SetTransform(&m);
	GraphicsManager::GetInstance()->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);

	LPDIRECT3DTEXTURE9 uiTexture = texture->GetTextureByIndex(currentTextureindex);
	LPDIRECT3DSURFACE9 desc;
	uiTexture->GetSurfaceLevel(0, &desc);

	D3DXVECTOR3 center = { 0,0,0 };//{ pivot.x * desc->Width, pivot.y * desc->Height, 0 };
	GraphicsManager::GetInstance()->GetSprite()->Draw(texture->GetTextureByIndex(currentTextureindex),
		NULL, &center, NULL, D3DCOLOR_RGBA(255, 255, 255, 255));
	GraphicsManager::GetInstance()->GetSprite()->End();
	GameObject::Render(dt);
}

void StaticUI::Free(void)
{
}
