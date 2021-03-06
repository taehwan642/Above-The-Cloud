#pragma once
#include "MonsterBase.h"
NAMESPACE(Engine)
class Transform;
END
class BossDashGun;
class BossShootGun;
class Boss final :
    public MonsterBase
{
private:
    BossDashGun* bossDashgunTop;
    BossDashGun* bossDashgunBottom;

    D3DXVECTOR3 revolveLerpPoint = { 0,0,0 };

    D3DXVECTOR3 revolvePos = { 0,0,0 };
    D3DXVECTOR3 revolvepos1 = { 0,150,0 };
    D3DXVECTOR3 revolvepos2 = { 0,-150,0 };

    Engine::Transform* revolvePoint = nullptr;
    Engine::Transform* t1 = nullptr;
    Engine::Transform* t2 = nullptr;

    float time = 0.f;
protected:
public:
    explicit Boss(void);
    virtual ~Boss(void);

    void SetInformation(const D3DXVECTOR3& _position) override;
   
    void Movement(const FLOAT& dt) override;

    INT Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};

