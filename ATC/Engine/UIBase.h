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
    std::wstring textureTag = L"";
    bool textureInitalized = false;
    UINT currentTextureindex = 0;
    
    explicit UIBase(void);
    virtual ~UIBase(void);
public:

    void SetInformation(const std::wstring& _textureTag, Transform* _parent = nullptr);
    void SetUITexture(const UINT& _index);
    
    INT Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};
END
