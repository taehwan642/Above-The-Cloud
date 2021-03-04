#pragma once
#include "MonsterBase.h"
class BossDashGun;
class BossShootGun;
class Boss final :
    public MonsterBase
{
private:
    BossDashGun* bossDashgunTop;
    BossDashGun* bossDashgunBottom;
protected:
public:
    explicit Boss(void);
    virtual ~Boss(void);

    void Movement(const FLOAT& dt) override;

    INT Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};

