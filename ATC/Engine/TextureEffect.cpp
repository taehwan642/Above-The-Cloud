#include "DXUT.h"
#include "Transform.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "TextureEffect.h"
USING(Engine)

TextureEffect::TextureEffect(const std::wstring& _texturetag, const D3DXVECTOR3& _position, Transform* _parent, const FLOAT& _alivetime) :
	DynamicUI(_texturetag, _parent),
	textureChangedelta(_alivetime)
{
	transform->position = _position;
}

TextureEffect::TextureEffect(const std::wstring& _texturetag, const D3DXVECTOR3& _position, const FLOAT& _alivetime) :
	DynamicUI(_texturetag),
	textureChangedelta(_alivetime)
{
	transform->position = _position;
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
		return OBJDEAD;
	DynamicUI::Update(dt);
	return OBJALIVE;
}

void TextureEffect::LateUpdate(const FLOAT& dt)
{
	DynamicUI::LateUpdate(dt);
}

void TextureEffect::Render(const FLOAT& dt)
{
	DynamicUI::Update(dt);
	DynamicUI::currentTextureindex = currentTextureIndex;
	DynamicUI::Render(dt);
}

void TextureEffect::Free(void)
{
	DynamicUI::Free();
}
