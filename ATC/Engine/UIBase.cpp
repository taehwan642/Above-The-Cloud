#include "DXUT.h"
#include "Transform.h"
#include "Texture.h"
#include "GraphicsManager.h"
#include "ResourceManager.h"
#include "UIBase.h"
USING(Engine)

UIBase::UIBase(void)
{

}

UIBase::UIBase(wstring _texturetag)
{
	texture = dynamic_cast<Texture*>(ResourceManager::GetInstance()->LoadResource(_texturetag));
	transform = new Transform();
	componentgroup.emplace(L"transform", transform);
}

UIBase::UIBase(wstring _texturetag, Transform* _parent)
{
	texture = dynamic_cast<Texture*>(ResourceManager::GetInstance()->LoadResource(_texturetag));
	transform = new Transform(_parent);
	componentgroup.emplace(L"transform", transform);
}

UIBase::~UIBase(void)
{

}

void UIBase::SetUITexture(const UINT& _index)
{
	currentTextureindex = _index;
}

void UIBase::Update(const FLOAT& dt)
{
	GameObject::Update(dt);
}

void UIBase::LateUpdate(const FLOAT& dt)
{
	GameObject::LateUpdate(dt);
}

void UIBase::Render(const FLOAT& dt)
{
	
}

void UIBase::Free(void)
{
	GameObject::Free();
}
