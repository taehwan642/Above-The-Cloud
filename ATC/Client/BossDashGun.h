#pragma once
#include "MonsterBase.h"
class BossDashGun final :
    public MonsterBase
{
private:
protected:
public:
    explicit BossDashGun(void);
    virtual ~BossDashGun(void);

    void Movement(const FLOAT& dt) override;

    INT Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};

