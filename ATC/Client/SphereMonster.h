#pragma once
#include "MonsterBase.h"
class SphereMonster final :
    public MonsterBase
{
private:
protected:
public:
    explicit SphereMonster(void);
    virtual ~SphereMonster(void);

    void Movement(void) override;

    void Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};

