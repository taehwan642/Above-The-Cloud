#pragma once
#include "MonsterBase.h"
class BossGuns :
    public MonsterBase
{
private:
protected:
public:
    bool isAttatched = false;

    explicit BossGuns(void);
    virtual ~BossGuns(void);

    void SetInformation(const D3DXVECTOR3& _position) override;
    void UnAttatch(void);

    INT Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};

