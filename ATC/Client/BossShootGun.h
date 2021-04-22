#pragma once
#include "BossGuns.h"
class BossShootGun final :
    public BossGuns
{
private:
protected:
public:
    explicit BossShootGun(void);
    virtual ~BossShootGun(void);

    void SetInformation(const D3DXVECTOR3& _position) override;

    void Movement(const FLOAT& dt) override;

    INT Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};