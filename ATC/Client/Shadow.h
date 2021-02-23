#pragma once
#include "../Engine/DynamicUI.h"

NAMESPACE(Engine)
class Transform;
END
class Shadow :
    public Engine::DynamicUI
{
private:
    Engine::Transform* objectTransform;
    D3DXVECTOR3 shadowScale = { 1,1,1 };
protected:
public:
    explicit Shadow(void);
    explicit Shadow(Engine::Transform* _objectTransform, const D3DXVECTOR3& _scale);
    virtual ~Shadow(void);

    INT Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};

