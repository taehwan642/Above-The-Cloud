#pragma once
#include "GameObject.h"

NAMESPACE(Engine)
class Transform;
class Texture;
class UIBase :
    public GameObject
{
private:
protected:
    D3DXVECTOR2 pivot = { 0.5f,0.5f };
    Transform* transform = nullptr;
    Texture* texture = nullptr;
    UINT currentTextureindex = 0;
public:
    explicit UIBase(void);
    explicit UIBase(wstring _texturetag);
    explicit UIBase(wstring _texturetag, Transform* _parent);
    virtual ~UIBase(void);

    void SetUITexture(const UINT& _index);
    
    void Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};
END
