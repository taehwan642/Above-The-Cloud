#pragma once
#include "../Engine/StaticUI.h"
class HealthPoint final :
    public Engine::StaticUI
{
private:
protected:
public:
    explicit HealthPoint(wstring _texturetag);
    virtual ~HealthPoint(void);

    INT Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};

