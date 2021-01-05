#pragma once
#include "../Engine/GameObject.h"
class MonsterBase :
    public Engine::GameObject
{
private:
protected:

public:
    explicit MonsterBase(void);
    virtual ~MonsterBase(void);

    void GetHit(const FLOAT& _damageamount);

    virtual void Movement(void) {};
    virtual void Attack(void) {};

    void Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};

