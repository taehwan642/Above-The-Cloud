#include "DXUT.h"
#include "RaycastManager.h"
USING(Engine)
void RaycastManager::GetRay(const D3DXMATRIX& _world)
{
    const D3DSURFACE_DESC* backbuffer = DXUTGetD3D9BackBufferSurfaceDesc();
    D3DXMATRIX matproj;
    DXUTGetD3D9Device()->GetTransform(D3DTS_PROJECTION, &matproj);

    POINT point = GetMousePoint();

    D3DXVECTOR3 v;
    v.x = (((2.0f * point.x) / backbuffer->Width) - 1) / matproj._11;
    v.y = -(((2.0f * point.y) / backbuffer->Height) - 1) / matproj._22;
    v.z = 1.0f;

    D3DXMATRIX matView;
    DXUTGetD3D9Device()->GetTransform(D3DTS_VIEW, &matView);
    D3DXMATRIX matWorld = _world;
    D3DXMATRIX WV = matWorld * matView;
    D3DXMATRIX m;
    D3DXMatrixInverse(&m, NULL, &WV);

    rayDir.x = v.x * m._11 + v.y * m._21 + v.z * m._31;
    rayDir.y = v.x * m._12 + v.y * m._22 + v.z * m._32;
    rayDir.z = v.x * m._13 + v.y * m._23 + v.z * m._33;

    rayPos.x = m._41;
    rayPos.y = m._42;
    rayPos.z = m._43;
}

POINT RaycastManager::GetMousePoint(void)
{
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(DXUTGetHWND(), &p);
	return p;
}

bool RaycastManager::PickMeshWithMouse(out float& _distanceOut, out D3DXVECTOR3& _targetposition, in const LPD3DXMESH& _mesh, in const D3DXMATRIX& _world)
{
	GetRay(_world);
	BOOL isHit;
	DWORD face;
	FLOAT u, v, distance;
	D3DXIntersect(_mesh, &rayPos, &rayDir, &isHit, &face, &u, &v, &distance, NULL, NULL);
	if (isHit)
	{
		_distanceOut = distance;
		_targetposition = rayPos + (rayDir * distance);
		return true;
	}
	return false;
}

bool RaycastManager::PickTriWithMouse(out FLOAT& _distanceOut, out D3DXVECTOR3& _triposition, in const D3DXVECTOR3& _p0, in const D3DXVECTOR3& _p1, in const D3DXVECTOR3& _p2, in const D3DXMATRIX& _world)
{
	FLOAT u, v, distance;
	GetRay(_world);
	if (D3DXIntersectTri(&_p0, &_p1, &_p2, &rayPos, &rayDir, &u, &v, &distance))
	{
		return true;
	}
	return false;
}

bool RaycastManager::PickMeshWithDirection(out float& _distanceOut, out D3DXVECTOR3& _targetposition, in const LPD3DXMESH& _mesh, in const D3DXVECTOR3& _direction, in const D3DXVECTOR3& _position, in const D3DXMATRIX& _world)
{
	BOOL isHit;
	DWORD face;
	FLOAT u, v, distance;

	D3DXMATRIX mat = _world;
	D3DXVECTOR3 pos = _position;
	D3DXVECTOR3 dir = _direction;
	D3DXMatrixInverse(&mat, 0, &mat);
	D3DXVec3TransformCoord(&pos, &pos, &mat);
	D3DXVec3TransformNormal(&dir, &dir, &mat);

	D3DXIntersect(_mesh, &pos, &dir, &isHit, &face, &u, &v, &distance, NULL, NULL);
	if (isHit)
	{
		_distanceOut = distance;
		_targetposition = _position + (_direction * distance);
		return true;
	}
	return false;
}