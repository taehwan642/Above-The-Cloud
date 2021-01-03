#pragma once
#include "UIBase.h"
NAMESPACE(Engine)
class StaticUI :
    public UIBase
{
private:
protected:
public:
    explicit StaticUI(void);
    explicit StaticUI(wstring _texturetag);
    virtual ~StaticUI(void);

    void SetPosition(const D3DXVECTOR2& _position);

    void Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};
END
