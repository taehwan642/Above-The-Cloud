#pragma once
#include "../Engine/DynamicUI.h"

NAMESPACE(Engine)
class Transform;
class Shadow;
END
class Shadow final :
    public Engine::DynamicUI
{
private:
    FLOAT alpha;
    Engine::Transform* objectTransform;
    Engine::Shader* shader;
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

