#pragma once
#include "../Engine/GameObject.h"

NAMESPACE(Engine)
class Transform;
class Shadow;
END

class Shadow final :
    public Engine::GameObject
{
private:
    INT alpha;
    Engine::Transform* transform = nullptr;
    Engine::Transform* objectTransform;
    Engine::Texture* texture = nullptr;
    D3DXVECTOR3 shadowScale = { 1,1,1 };

    LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL;
    LPDIRECT3DINDEXBUFFER9 g_pIB = NULL;
    struct CUSTOMVERTEX
    {
        FLOAT x, y, z;      // The untransformed, 3D position for the vertex
        DWORD color;        // The vertex color
        FLOAT u, v;
    };
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)

protected:
public:
    HRESULT Initialize(void);

    explicit Shadow(void);
    explicit Shadow(Engine::Transform* _objectTransform, const D3DXVECTOR3& _scale);
    virtual ~Shadow(void);

    void ResetSize(void);

    INT Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};

