#pragma once
#include "Singleton.h"
NAMESPACE(Engine)
class RaycastManager final :
    public Singleton<RaycastManager>
{
private:
    D3DXVECTOR3 rayPos;
    D3DXVECTOR3 rayDir;

    void GetRay(const D3DXMATRIX& _world);
protected:
public:
    POINT GetMousePoint(void);
    BOOL PickMeshWithMouse(out float& _distanceOut,
                  out D3DXVECTOR3& _targetposition,
                  in const LPD3DXMESH& _mesh, 
                  in const D3DXMATRIX& _world);

    BOOL PickMeshWithDirection(out float& _distanceOut,
        out D3DXVECTOR3& _targetposition,
        in const LPD3DXMESH& _mesh,
        in const D3DXVECTOR3& _direction,
        in const D3DXVECTOR3& _position,
        in const D3DXMATRIX& _world);

};
END