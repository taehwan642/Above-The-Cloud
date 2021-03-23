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
    BossDashGun* bossDashGuns[2];
    BossShootGun* bossShootGuns[2];

    D3DXVECTOR3 revolveLerpPoint = { 0,0,0 };

    Engine::Transform* revolvePoint = nullptr;
    Engine::Transform* gunTransforms[4];
    float theta[4];

    float defaultRadius = 120.f;
    float defaultSpeed = 3.f;

    float radius = 120.f;
    float speed = 3.f;

    float delta = 0.f;

protected:
public:
    explicit Boss(void);
    virtual ~Boss(void);

    void SetInformation(const D3DXVECTOR3& _position) override;
    void DieAction(void) override;

    void Movement(const FLOAT& dt) override;

    INT Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};

