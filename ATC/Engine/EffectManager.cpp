#include "DXUT.h"
#include "Layer.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "TextureEffect.h"
#include "Transform.h"
#include "EffectManager.h"
USING(Engine)

void EffectManager::SpawnTextureEffect(const D3DXVECTOR3& _position, const D3DXVECTOR3& _scale, Transform* _transform, const FLOAT& _alivetime, const std::wstring& _texturetag, const std::wstring& _layertag)
{
	
	TextureEffect* texeffect;
	// 현재 씬의 Tag에 맞는 레이어 속에다 _alivetime전까지 살아있는 GameObject 생성해서 넣어주기
	if (_transform != nullptr)
		texeffect = new TextureEffect(_texturetag, _position, _scale, _transform, _alivetime);
	else
		texeffect = new TextureEffect(_texturetag, _position, _scale, _alivetime);

	SceneManager::GetInstance()->AddGameObject(OBJ2, _layertag, texeffect);
	return;
}
