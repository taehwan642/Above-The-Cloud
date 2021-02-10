#pragma once
#include "DynamicUI.h"
NAMESPACE(Engine)
class Button :
    public DynamicUI
{
private:
    function<void(void)> buttonFunction;
protected:
public:
    explicit Button(void);
    explicit Button(const wstring& _texturetag);
    virtual ~Button(void);

    INT Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void SetButtonFunction(function<void(void)> _function);
    function<void(void)> GetButtonFunction(void) const;

    void Free(void) override;
};
END