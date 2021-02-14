#pragma once
#include "MonsterBase.h"
class Monster2 final :
    public MonsterBase
{
private:
protected:
public:
    explicit Monster2(void);
    virtual ~Monster2(void);

    void Movement(const FLOAT& dt) override;

    INT Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};

