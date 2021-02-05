#pragma once
#include "DynamicUI.h"
NAMESPACE(Engine)
class Transform;
class Texture;
class TextureEffect final :
    public DynamicUI
{
    // 정해진 시간이 지날때마다 texture++; 시키고 texture == 최대텍스쳐가 되면 active false
private:
    FLOAT textureChangedelta = 0.3f;
    FLOAT alivetime = 0.0f;
    INT currentTextureIndex = 0;
protected:
public:
    explicit TextureEffect(const wstring& _texturetag, const D3DXVECTOR3& _position, Transform* _parent, const FLOAT& _alivetime = 0.3f);
    explicit TextureEffect(const wstring& _texturetag, const D3DXVECTOR3& _position, const FLOAT& _alivetime = 0.3f);
    virtual ~TextureEffect(void);

    INT Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};
END