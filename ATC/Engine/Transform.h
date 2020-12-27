#pragma once
#include "Component.h"

NAMESPACE(Engine)
class Transform final :
    public Component
{
private:
    Transform* parent = nullptr;
protected:
public:
    explicit Transform(void);
    explicit Transform(Transform* _parent);
    virtual ~Transform(void);

public:
    enum RotType : unsigned short { RIGHT, UP, LOOK };

    D3DXVECTOR3 position;
    D3DXVECTOR3 rotation;

    D3DXQUATERNION quaternion;
    D3DXQUATERNION curQuaternion;

    D3DXVECTOR3 scale;
    
    D3DXMATRIX worldMatrix;

    void Update(const float& dt) override;

    void SetParent(Transform* _parent);
    void ReleaseParent(void);

    void Rotate(RotType _rotType, float _angle);

    void Free(void) override {};
};
END