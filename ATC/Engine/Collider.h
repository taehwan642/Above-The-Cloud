#pragma once
#include "Component.h"
NAMESPACE(Engine)
class CollisionSphere;
class Collider final :
    public Component
{
private:
    CollisionSphere* sphere;
    FLOAT radius;
    D3DXVECTOR3* center;
protected:
public:

    explicit Collider(const FLOAT& _radius, D3DXVECTOR3* _center);
    virtual ~Collider(void);

    FLOAT GetRadius(void) { return radius; }
    LPD3DXVECTOR3 GetCenter(void) { return center; }

    void RenderCollider(void);

    void Free(void) override;
};
END