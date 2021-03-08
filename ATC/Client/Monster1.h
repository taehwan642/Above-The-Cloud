#pragma once
#include "MonsterBase.h"
class Monster1 final :
    public MonsterBase
{
private:
protected:
public:
    explicit Monster1(void);
    virtual ~Monster1(void);

    void SetInformation(const D3DXVECTOR3& _position);

    void Movement(const FLOAT& dt) override;

    INT Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};