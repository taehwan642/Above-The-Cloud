#include "DXUT.h"
#include "Layer.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "TextureEffect.h"
#include "EffectManager.h"
USING(Engine)

void EffectManager::SpawnTextureEffect(const D3DXVECTOR3& _position, Transform* _transform, const FLOAT& _alivetime, const wstring& _texturetag, const wstring& _layertag)
{
	// 현재 씬의 Tag에 맞는 레이어 속에다 _alivetime전까지 살아있는 GameObject 생성해서 넣어주기
	TextureEffect* texeffect = new TextureEffect(_texturetag, _position, _transform, _alivetime);
	//texeffect->CreateTextureEffect(_texturetag, _position, _transform);
	SceneManager::GetInstance()->AddGameObject(L"Effect", _layertag, texeffect);
	return;
}
