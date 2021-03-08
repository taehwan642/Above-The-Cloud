#pragma once
#include "MonsterBase.h"
class BossShootGun final :
    public MonsterBase
{
private:
protected:
public:
    bool isAttatched = false;

    explicit BossShootGun(void);
    virtual ~BossShootGun(void);

    void SetInformation(const D3DXVECTOR3& _position) override;

    void Movement(const FLOAT& dt) override;

    INT Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};