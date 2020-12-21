#include "DXUT.h"
#include "Transform.h"

USING(Engine)
Transform::Transform(void) :
	position(0,0,0),
	rotation(0, 0, 0),
	scale(1, 1, 1),
	worldMatrix(D3DXMATRIX())
{}

Transform::Transform(Transform* _parent) :
	position(0, 0, 0),
	rotation(0, 0, 0),
	scale(1, 1, 1),
	worldMatrix(D3DXMATRIX()),
	parent(_parent)
{
	parent->AddReference();
}

Transform::~Transform(void)
{
	if (parent)
		parent->Release();
}

void Transform::Update(const float& dt)
{
	D3DXMATRIX S, R, T;
	
	D3DXMatrixScaling(&S, scale.x, scale.y, scale.z);
	D3DXMatrixRotationYawPitchRoll(&R, rotation.y, rotation.x, rotation.z);
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);

	worldMatrix = S * R * T;
	if (parent != nullptr)
		worldMatrix *= parent->worldMatrix;
}
