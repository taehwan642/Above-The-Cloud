#include "DXUT.h"
#include "Layer.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "TextureEffect.h"
#include "Transform.h"
#include "ObjectManager.h"
#include "EffectManager.h"
USING(Engine)

void EffectManager::SpawnTextureEffect(const D3DXVECTOR3& _position, const D3DXVECTOR3& _scale, Transform* _transform, const FLOAT& _alivetime, const std::wstring& _texturetag, const std::wstring& _layertag)
{
	TextureEffect* texeffect = ObjectManager::GetInstance()->GetActiveFalsedObject<TextureEffect>(EFFECT, _layertag);
	
	if (texeffect == nullptr)
	{
		texeffect = new TextureEffect();
		texeffect->SetInformation(_texturetag, _position, _scale, _transform, _alivetime);
		SceneManager::GetInstance()->AddGameObject(EFFECT, _layertag, texeffect);
	}
	else
	{
		texeffect->SetInformation(_texturetag, _position, _scale, _transform, _alivetime);
	}

	return;
}
