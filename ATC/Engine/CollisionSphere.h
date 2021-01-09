#pragma once
#include "Component.h"
NAMESPACE(Engine)
class CollisionSphere final : // Compute
    public Component
{
private:
    LPD3DXMESH sphere = nullptr;
protected:
public:
    explicit CollisionSphere(const FLOAT& _radius);
    virtual ~CollisionSphere(void) {};
    
    void CreateSphere(const FLOAT& _radius);

    void RenderSphere(void);

    void Free(void) override;
};
END