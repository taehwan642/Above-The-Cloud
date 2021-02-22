#pragma once
#include "../Engine/DynamicUI.h"

class PlayerObserver;
class PlaneShadow :
    public Engine::DynamicUI
{
private:
    PlayerObserver* observer = nullptr;
protected:
public:
    explicit PlaneShadow(void);
    virtual ~PlaneShadow(void);

    INT Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};

