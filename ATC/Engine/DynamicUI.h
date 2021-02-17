#pragma once
#include "UIBase.h"
NAMESPACE(Engine)
class DynamicUI :
    public UIBase
{
private:
    bool isbillboard = true;
    void CreateBuffer(void);
protected:
    LPDIRECT3DVERTEXBUFFER9 vb;
    LPDIRECT3DINDEXBUFFER9 ib; 
    DWORD vtxsize = 0;
    DWORD vtxcnt = 0;
    DWORD vtxFVF = 0;
    DWORD tricnt = 0;
    DWORD idxsize = 0;
    D3DFORMAT idxfmt;
public:
    explicit DynamicUI(void);
    virtual ~DynamicUI(void);

    INT Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void SetBillBoardEnable(bool _isbillboardenable)
    {
        isbillboard = _isbillboardenable;
    };

    void Free(void) override;
};
END