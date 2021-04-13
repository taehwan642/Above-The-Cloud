#pragma once
#include "../Engine/StaticUI.h"

class RadarDot;
class PlayerObserver;
class RadarPlane final :
    public Engine::StaticUI
{
private:
    D3DXVECTOR3 testPosition = { 0,0,0 };
    PlayerObserver* observer = nullptr;
    std::vector<D3DXVECTOR3> dotpositions;
    std::vector<RadarDot*> dots;

protected:
public:
    explicit RadarPlane(void);
    virtual ~RadarPlane(void);

    INT Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};

