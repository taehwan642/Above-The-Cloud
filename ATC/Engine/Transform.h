#pragma once
#include "Component.h"

NAMESPACE(Engine)
class Transform final :
	public Component
{
private:
protected:
public:
	Transform* parent = nullptr;
	explicit Transform(void);
	explicit Transform(Transform* _parent);
	virtual ~Transform(void);

public:
	enum RotType : unsigned short { RIGHT, UP, LOOK };

	D3DXVECTOR3 localPosition;
	D3DXVECTOR3 rotation;

	D3DXQUATERNION quaternion;
	D3DXQUATERNION curQuaternion;

	D3DXVECTOR3 scale;

	D3DXMATRIX worldMatrix;

	D3DXVECTOR3 worldPosition;

	FLOAT slerpSpeed = 3.f;
	bool quaternionMode = true;

	void Update(const FLOAT& dt) override;

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

	static D3DXVECTOR3 rotationMatrixToEulerAngles(D3DXMATRIX& R)
	{
		float sy = sqrt(R._11 * R._11 + R._21 * R._21);

		bool singular = sy < 1e-6; // If

		float x, y, z;
		if (!singular)
		{
			x = atan2(R._32, R._33);
			y = atan2(-R._31, sy);
			z = atan2(R._21, R._11);
		}
		else
		{
			x = atan2(-R._23, R._22);
			y = atan2(-R._31, sy);
			z = 0;
		}

		D3DXVECTOR3 result{ x,y,z };
		return result;
	}


	void Free(void) override;
};
END