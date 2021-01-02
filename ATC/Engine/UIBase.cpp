#include "DXUT.h"
#include "Transform.h"
#include "Texture.h"
#include "GraphicsManager.h"
#include "UIBase.h"
USING(Engine)

UIBase::UIBase(void)
{

}

UIBase::UIBase(wstring _texturetag)
{
}

UIBase::~UIBase(void)
{

}

void UIBase::SetPosition(const D3DXVECTOR2& _position)
{
	transform->position.x = _position.x;
	transform->position.y = _position.y;
}

void UIBase::SetUITexture(const UINT& _index)
{

}

void UIBase::Update(const FLOAT& dt)
{

}

void UIBase::LateUpdate(const FLOAT& dt)
{

}

void UIBase::Render(const FLOAT& dt)
{
	
}
