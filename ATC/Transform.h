#pragma once
#include "Component.h"

NAMESPACE(Engine)
class Transform :
    public Component
{
public:
    explicit Transform(void);
    explicit Transform(Transform* _parent);
    virtual ~Transform(void);

    Transform* parent = nullptr;

    D3DXVECTOR3 position;
    D3DXVECTOR3 rotation;
    D3DXVECTOR3 scale;
    
    D3DXMATRIX worldMatrix;

    void Update(const float& dt) override;
};
END