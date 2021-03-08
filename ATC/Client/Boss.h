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

