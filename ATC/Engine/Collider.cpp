#include "DXUT.h"
#include "CollisionSphere.h"
#include "Collider.h"
USING(Engine)

Collider::Collider(const FLOAT& _radius)
{
	sphere = new CollisionSphere(_radius);
	radius = _radius;
}

Collider::~Collider(void)
{
}

void Collider::RenderCollider(const D3DXMATRIX& _position)
{
	DEVICE->SetTransform(D3DTS_WORLD, &_position);
	DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);
	sphere->RenderSphere();
	DEVICE->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

void Collider::Free(void)
{
	Safe_Release(sphere);
}
