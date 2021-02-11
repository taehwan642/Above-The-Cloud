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
    explicit StaticUI(std::wstring _texturetag);
    explicit StaticUI(std::wstring _texturetag, Transform* _parent);
    virtual ~StaticUI(void);

    void SetPosition(const D3DXVECTOR2& _position);

    INT Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};
END
