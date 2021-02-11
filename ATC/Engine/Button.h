#pragma once
#include "DynamicUI.h"
NAMESPACE(Engine)
class Button final :
    public DynamicUI
{
private:
    std::function<void(void)> buttonFunction;
protected:
public:
    explicit Button(const std::wstring& _texturetag, const D3DXVECTOR3& _position);
    virtual ~Button(void);

    INT Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    bool IsMouseOn(void);

    void SetButtonFunction(std::function<void(void)> _function);
    std::function<void(void)> GetButtonFunction(void) const;

    void Free(void) override;
};
END