#include "DXUT.h"
#include "CollisionSphere.h"
USING(Engine)

CollisionSphere::CollisionSphere(const FLOAT& _radius)
{
	CreateSphere(_radius);
}


void CollisionSphere::CreateSphere(const FLOAT& _radius)
{
	D3DXCreateSphere(DEVICE, _radius, 20, 20, &sphere, nullptr);
}

void CollisionSphere::RenderSphere(void)
{
	sphere->DrawSubset(0);
}

void CollisionSphere::Free(void)
{
	sphere->Release();
}
