#pragma once
#include "Component.h"
NAMESPACE(Engine)
class CollisionSphere;
class Collider final :
    public Component
{
private:
    CollisionSphere* sphere;
protected:
public:
    FLOAT radius;

    explicit Collider(const FLOAT& _radius);
    virtual ~Collider(void);

    void RenderCollider(const D3DXMATRIX& _position);

    void Free(void) override;
};
END