#pragma once
#include "../Engine/StaticUI.h"

class RadarDot;
class PlayerObserver;
class RadarPlane final :
    public Engine::StaticUI
{
private:
    D3DXVECTOR3 testPosition = { 5,5,50 };
    PlayerObserver* observer = nullptr;
    std::vector<std::pair<RadarDot*, D3DXVECTOR3>> dotpositions;

protected:
public:
    explicit RadarPlane(void);
    virtual ~RadarPlane(void);

    INT Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};

