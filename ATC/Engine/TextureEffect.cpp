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
	DynamicUI::Update(dt);
	if (texturesize <= currentTextureIndex)
		isActive = false;
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

void TextureEffect::SetInformation(const std::wstring& _texturetag, const D3DXVECTOR3& _position, const D3DXVECTOR3& _scale, Transform* _parent, const FLOAT& _alivetime)
{
	UIBase::SetInformation(_texturetag, _parent);
	currentTextureIndex = 0;
	textureChangedelta = _alivetime;
	transform->position = _position;
	memcpy(&transform->worldMatrix._41, &transform->position, sizeof(D3DXVECTOR3));
	transform->scale = _scale;
	isActive = true;
}

void TextureEffect::Free(void)
{
	DynamicUI::Free();
}
