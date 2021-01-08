#pragma once
#include "UIBase.h"
NAMESPACE(Engine)
class DynamicUI : // Buffer 사용한 Billboard. Enemy Lock & AimPoint같은 동적 UI를 위한 클래스
    public UIBase
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
    bool isbillboard = true;
    void CreateBuffer(void);
protected:
public:
    explicit DynamicUI(wstring _texturetag, bool _billboardenable = true);
    explicit DynamicUI(wstring _texturetag, Transform* _parent, bool _billboardenable = true);
    virtual ~DynamicUI(void);

    void Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};
END