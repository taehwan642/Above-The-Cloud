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
    Engine::Transform* transform = nullptr;
    Engine::Transform* objectTransform = nullptr;
    Engine::Texture* texture = nullptr;
    LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL;
    LPDIRECT3DINDEXBUFFER9 g_pIB = NULL;
    struct CUSTOMVERTEX
    {
        FLOAT x, y, z;      // The untransformed, 3D position for the vertex
        DWORD color;        // The vertex color
        FLOAT u, v;
    };
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)

public:
    explicit ShadowTest();
    HRESULT Initialize(void);
    INT Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;
    void Free(void) override;
};

