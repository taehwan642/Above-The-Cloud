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

    D3DXVECTOR3 localPosition;
    D3DXVECTOR3 worldPosition;

    void Update(const float& dt) override;

    void SetParent(Transform* _parent);
    void ReleaseParent(void);

    void Rotate(RotType _rotType, float _angle);

    bool Lerp(D3DXVECTOR3& _position, const D3DXVECTOR3& _destination, const FLOAT& _dt, const FLOAT& _distance = 0.5f)
    {
        D3DXVec3Lerp(&_position, &_position, &_destination, _dt);
        if (D3DXVec3Length(&D3DXVECTOR3(_position - _destination)) < _distance)
        {
            return true;
        }
        return false;
    }

    void Free(void) override;
};
END