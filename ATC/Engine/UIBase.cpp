#include "DXUT.h"
#include "Transform.h"
#include "Texture.h"
#include "GraphicsManager.h"
#include "ResourceManager.h"
#include "UIBase.h"
USING(Engine)

UIBase::UIBase(void)
{
	texture = new Texture();
	transform = new Transform();
	componentgroup.emplace(L"Transform", transform);
}

UIBase::~UIBase(void)
{
}

void UIBase::SetInformation(const std::wstring& _textureTag, Transform* _parent)
{
	if (textureTag != _textureTag)
	{
		Safe_Release(texture);
		texture = dynamic_cast<Texture*>(ResourceManager::GetInstance()->LoadResource(_textureTag));
		textureTag = _textureTag;
	}
	if (_parent != nullptr)
		transform->SetParent(_parent);
}

void UIBase::SetUITexture(const UINT& _index)
{
	currentTextureindex = _index;
}

INT UIBase::Update(const FLOAT& dt)
{
	GameObject::Update(dt);
	return OBJALIVE;
}

void UIBase::LateUpdate(const FLOAT& dt)
{
	GameObject::LateUpdate(dt);
}

void UIBase::Render(const FLOAT& dt)
{
	GameObject::Render(dt);
}

void UIBase::Free(void)
{
	Safe_Release(texture);
	GameObject::Free();
}
