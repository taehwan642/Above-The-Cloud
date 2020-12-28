#include "DXUT.h"
#include "Transform.h"

USING(Engine)
Transform::Transform(void) :
	position(0,0,0),
	rotation(0, 0, 0),
	scale(1, 1, 1)
{
	D3DXMatrixIdentity(&worldMatrix);
	D3DXQuaternionIdentity(&quaternion);
	D3DXQuaternionIdentity(&curQuaternion);
}

Transform::Transform(Transform* _parent) :
	position(0, 0, 0),
	rotation(0, 0, 0),
	scale(1, 1, 1)
{
	SetParent(_parent);
	D3DXMatrixIdentity(&worldMatrix);
	D3DXQuaternionIdentity(&quaternion);
	D3DXQuaternionIdentity(&curQuaternion);
}

Transform::~Transform(void)
{
	ReleaseParent();
}

void Transform::SetParent(Transform* _parent)
{
	ReleaseParent();
	parent = _parent;
	parent->AddReference();
}

void Transform::ReleaseParent(void)
{
	if (parent != nullptr)
	{
		parent->Release();
		parent = nullptr;
	}
}


void Transform::Rotate(RotType _rotType, float _angle)
{
	D3DXVECTOR3 axis = *reinterpret_cast<D3DXVECTOR3*>(&worldMatrix.m[_rotType][0]);

	D3DXQUATERNION rot;
	D3DXQuaternionRotationAxis(&rot, &axis, _angle);
	quaternion *= rot;
}

void Transform::Update(const float& dt)
{
	D3DXMATRIX S, R, T;
	D3DXMATRIX rx, ry, rz;
	D3DXMatrixScaling(&S, scale.x, scale.y, scale.z);
	
	D3DXQuaternionSlerp(&curQuaternion, &curQuaternion, &quaternion, dt * 3);

	D3DXMATRIX matRot;
	D3DXMatrixRotationQuaternion(&matRot, &curQuaternion);

	D3DXMatrixTranslation(&T, position.x, position.y, position.z);

	worldMatrix = S * matRot * T;
	if (parent != nullptr)
		worldMatrix *= parent->worldMatrix;
}
