#pragma once
#include "MonsterBase.h"
class Monster2 final :
    public MonsterBase
{
private:
    D3DXVECTOR3 moveDirection = { 0,0,0 };
protected:
public:
    explicit Monster2(void);
    virtual ~Monster2(void);

    void Movement(const FLOAT& dt) override;

    void SetInformation(const D3DXVECTOR3& _position) override;

    INT Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};

