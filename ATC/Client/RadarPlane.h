#pragma once
#include "../Engine/StaticUI.h"

class RadarDot;
class RadarPlane final :
    public Engine::StaticUI
{
private:
    std::list<RadarDot*> radardots;

protected:
public:
    explicit RadarPlane(void);
    virtual ~RadarPlane(void);

    INT Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};

