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
	scale(1, 1, 1),
	parent(_parent)
{
	parent->AddReference();
	D3DXMatrixIdentity(&worldMatrix);
	D3DXQuaternionIdentity(&quaternion);
}

Transform::~Transform(void)
{
	if (parent)
		parent->Release();
}

void Transform::Rotate(RotType _rotType, float _angle)
{
	D3DXVECTOR3 axis = *reinterpret_cast<D3DXVECTOR3*>(&worldMatrix.m[_rotType][0]);

	float axisScale = D3DXVec3Length(&axis);

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
	cout << position.x << endl;
	worldMatrix = S * matRot * T;
	if (parent != nullptr)
		worldMatrix *= parent->worldMatrix;
}
