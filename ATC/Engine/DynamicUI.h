#pragma once
#include "UIBase.h"
NAMESPACE(Engine)
class DynamicUI : // Buffer ����� Billboard. Enemy Lock & AimPoint���� ���� UI�� ���� Ŭ����
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
protected:
public:
    explicit DynamicUI(wstring _texturetag);
    virtual ~DynamicUI(void);

    void Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};
END