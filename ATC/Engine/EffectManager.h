#pragma once
#include "Singleton.h"
NAMESPACE(Engine)
class Transform;
class EffectManager :
    public Singleton<EffectManager>
{
private:
protected:
public:
    void SpawnTextureEffect(const D3DXVECTOR3& _position,
                            const D3DXVECTOR3& _scale,
                            Transform* _transform,
                            const FLOAT& _alivetime,
                            const std::wstring& _texturetag,
                            const std::wstring& _layertag = L"Effect");
};
END