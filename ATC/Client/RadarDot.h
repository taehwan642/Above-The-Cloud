#pragma once
#include "../Engine/StaticUI.h"

class RadarDot :
    public Engine::StaticUI
{
private:
protected:
public:
    void SetPosition(const D3DXVECTOR3& _position);

    explicit RadarDot(void);
    virtual ~RadarDot(void);

    INT Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};

