#pragma once
#include "BossGuns.h"
class BossDashGun final :
    public BossGuns
{
private:
    float delta{ 0.f };
protected:
public:
    explicit BossDashGun(void);
    virtual ~BossDashGun(void);

    void SetInformation(const D3DXVECTOR3& _position) override;

    void Movement(const FLOAT& dt) override;

    INT Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};

