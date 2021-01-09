#include "DXUT.h"
#include "CollisionSphere.h"
#include "Collider.h"
USING(Engine)

Collider::Collider(const FLOAT& _radius, D3DXVECTOR3* _center, ObjectTag _tag)
{
	sphere = new CollisionSphere(_radius);
	radius = _radius;
	center = _center;
	tag = _tag;
}

Collider::~Collider(void)
{
}

void Collider::RenderCollider()
{
	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans, center->x, center->y, center->z);
	DEVICE->SetTransform(D3DTS_WORLD, &matTrans);
	DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);
	sphere->RenderSphere();
	DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

void Collider::Free(void)
{
	Safe_Release(sphere);
}
