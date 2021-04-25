#include "DXUT.h"
#include "../Engine/Transform.h"
#include "../Engine/DynamicMesh.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/SubjectManager.h"
#include "../Engine/Shader.h"
#include "../Engine/Trail.h"
#include "../Engine/CollisionManager.h"
#include "../Engine/Collider.h"
#include "PlayerObserver.h"
#include "../Engine/ObjectManager.h"
#include "BossGuns.h"

BossGuns::BossGuns(void)
{
}

BossGuns::~BossGuns(void)
{
}

void BossGuns::SetInformation(const D3DXVECTOR3& _position)
{
	if (isAttatched == false)
		Engine::CollisionManager::GetInstance()->PushData(MONSTER, this);
	MonsterBase::SetInformation(_position);
}

void BossGuns::UnAttatch(void)
{
	Engine::CollisionManager::GetInstance()->PushData(MONSTER, this);
}

INT BossGuns::Update(const FLOAT& dt)
{
	return MonsterBase::Update(dt);
}

void BossGuns::LateUpdate(const FLOAT& dt)
{
	D3DXVECTOR3 look = observer->GetTransform()->localPosition - transform->localPosition;
	D3DXVec3Normalize(&look, &look);

	D3DXVECTOR3 right;
	D3DXVec3Cross(&right, &D3DXVECTOR3(0, 1, 0), &look);
	D3DXVec3Normalize(&right, &right);

	D3DXVECTOR3 up;
	D3DXVec3Cross(&up, &look, &right);
	D3DXVec3Normalize(&up, &up);

	D3DXMATRIX matRot;
	D3DXMatrixIdentity(&matRot);
	memcpy(&matRot._11, &right, sizeof(D3DXVECTOR3));
	memcpy(&matRot._21, &up, sizeof(D3DXVECTOR3));
	memcpy(&matRot._31, &look, sizeof(D3DXVECTOR3));
	D3DXQuaternionRotationMatrix(&transform->quaternion, &matRot);
	MonsterBase::LateUpdate(dt);
}

void BossGuns::Render(const FLOAT& dt)
{
	MonsterBase::Render(dt);
}

void BossGuns::Free(void)
{
	MonsterBase::Free();
}
