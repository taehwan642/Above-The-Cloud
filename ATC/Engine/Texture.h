#pragma once
#include "Resources.h"
NAMESPACE(Engine)
class Texture final :
    public Resources
{
private:
    vector<LPDIRECT3DTEXTURE9> textures;
    size_t texturescount = 0;
protected:
public:
    explicit Texture(void);
    explicit Texture(const Texture& cp);
    virtual ~Texture(void);

    size_t GetTexturesCount(void) { return texturescount; }

    HRESULT LoadTexture(wstring _filepath, const UINT& _texturecount = 1);

    void RenderTexture(LPD3DXEFFECT& _effect, const UINT& _index = 0);
    void RenderTexture(const UINT& _index = 0);

    void Update(const FLOAT& dt) override {};
    void Render(const FLOAT& dt) override;

    Resources* Clone(void) override;
    void Free(void) override;
};
END