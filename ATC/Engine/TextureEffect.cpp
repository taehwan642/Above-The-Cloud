#include "DXUT.h"
#include "Transform.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "RenderManager.h"
#include "TextureEffect.h"
USING(Engine)

TextureEffect::TextureEffect(void)
{
}

TextureEffect::~TextureEffect(void)
{
}

INT TextureEffect::Update(const FLOAT& dt)
{
	alivetime += dt;
	if (alivetime > textureChangedelta)
	{
		alivetime = 0;
		++currentTextureIndex;
	}

	size_t texturesize = texture->GetTexturesCount();
	if (texturesize <= currentTextureIndex)
		isActive = false;
	DynamicUI::Update(dt);
	if (isActive == true)
		Engine::RenderManager::GetInstance()->AddRenderObject(ID_EFFECT, this);
	return OBJALIVE;
}

void TextureEffect::LateUpdate(const FLOAT& dt)
{
	DynamicUI::LateUpdate(dt);
}

void TextureEffect::Render(const FLOAT& dt)
{
	DynamicUI::currentTextureindex = currentTextureIndex;
	DynamicUI::Render(dt);
}

void TextureEffect::SetInformation(const std::wstring& _texturetag, const D3DXVECTOR3& _position, const D3DXVECTOR3& _scale, Transform* _parent, const FLOAT& _alivetime)
{
	UIBase::SetInformation(_texturetag, _parent);
	isActive = true;
	currentTextureIndex = 0;
	textureChangedelta = _alivetime;
	transform->position = _position;
	transform->scale = _scale;
}

void TextureEffect::Free(void)
{
	DynamicUI::Free();
}
