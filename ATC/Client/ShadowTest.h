#pragma once
#include "../Engine/GameObject.h"

NAMESPACE(Engine)
class Transform;
class Texture;
END

class ShadowTest :
    public Engine::GameObject
{
private:
    LPDIRECT3DVERTEXBUFFER9 vb;
    LPDIRECT3DINDEXBUFFER9 ib;
    DWORD vtxsize = 0;
    DWORD vtxcnt = 0;
    DWORD vtxFVF = 0;
    DWORD tricnt = 0;
    DWORD idxsize = 0;
    D3DFORMAT idxfmt;

    Engine::Transform* transform = nullptr;
    Engine::Texture* texture = nullptr;

public:
    explicit ShadowTest();
    INT Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;
    void Free(void) override;
};

