#include "DXUT.h"
#include "Transform.h"

USING(Engine)
Transform::Transform(void) :
	position(D3DXVECTOR3()),
	rotation(D3DXVECTOR3()),
	scale(D3DXVECTOR3()),
	worldMatrix(D3DXMATRIX())
{}

Transform::Transform(Transform* _parent) :
	position(D3DXVECTOR3()),
	rotation(D3DXVECTOR3()),
	scale(D3DXVECTOR3()),
	worldMatrix(D3DXMATRIX()),
	parent(_parent)
{
	parent->AddReference();
}

Transform::~Transform(void)
{
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
