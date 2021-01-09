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
    ObjectTag tag;
protected:
public:
    ObjectTag collisiontag;
    BOOL ishit = false;

    explicit Collider(const FLOAT& _radius, D3DXVECTOR3* _center, ObjectTag _tag);
    virtual ~Collider(void);

    FLOAT GetRadius(void) { return radius; }
    LPD3DXVECTOR3 GetCenter(void) { return center; }
    ObjectTag GetTag(void) { return tag; }

    void RenderCollider(void);

    void Free(void) override;
};
END