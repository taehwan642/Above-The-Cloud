#include "DXUT.h"
#include "../Engine/Camera.h"
#include "../Engine/Transform.h"
#include "MonsterInfoManager.h"
#include "CutSceneCamera.h"

CutSceneCamera::CutSceneCamera(void)
{
	transform = new Engine::Transform();
	componentgroup.emplace(L"Transform", transform);
	camera = new Engine::Camera();
	componentgroup.emplace(L"Camera", camera);
	camera->SetProjectionMatrix(D3DXToRadian(70),
		static_cast<FLOAT>(DXUTGetD3D9BackBufferSurfaceDesc()->Width) /
		static_cast<FLOAT>(DXUTGetD3D9BackBufferSurfaceDesc()->Height),
		1,
		500);
}

CutSceneCamera::~CutSceneCamera(void)
{
}

void
CutSceneCamera::SetCutSceneIndex(CUTSCENEINDEX _index)
{
	index = _index;
}

CUTSCENEINDEX
CutSceneCamera::GetCutSceneIndex(void) const
{
	return index;
}

void
CutSceneCamera::LookAtBoss(void)
{
	// 1. MonsterObserver�� ��ġ �޾Ƽ�
	std::list<Engine::Transform*> list = MonsterInfoManager::GetInstance()->GetListWithMonsterType(BOSS);
	// 2. �������� Ȯ���ϰ�
	// 3. ������� �� ��ġ �ּ� �޾Ƽ� �ٶ󺸰� �ϱ�
	Engine::Transform* t = *list.begin(); // ������ ������ �ϳ��� �����ϱ⿡.
	//std::cout << "LIST : " << t->localPosition.x << " " << t->localPosition.y << " " << t->localPosition.z << " " << std::endl;
	// �� �׽�Ʈ ����.
	// 
	// 4. �ð��� ������ �ٽ� ���� �����ٰ� �÷��� �����
	D3DXVECTOR3 playerlook = t->localPosition - transform->localPosition;
	D3DXVec3Normalize(&playerlook, &playerlook);

	D3DXVECTOR3 right;
	D3DXVec3Cross(&right, &D3DXVECTOR3(0, 1, 0), &playerlook);
	D3DXVec3Normalize(&right, &right);

	D3DXVECTOR3 up;
	D3DXVec3Cross(&up, &playerlook, &right);
	D3DXVec3Normalize(&up, &up);

	D3DXMATRIX matRot;
	D3DXMatrixIdentity(&matRot);
	memcpy(&matRot._11, &right, sizeof(D3DXVECTOR3));
	memcpy(&matRot._21, &up, sizeof(D3DXVECTOR3));
	memcpy(&matRot._31, &playerlook, sizeof(D3DXVECTOR3));
	D3DXQuaternionRotationMatrix(&transform->quaternion, &matRot);
}

INT 
CutSceneCamera::Update(const FLOAT& dt)
{
	return GameObject::Update(dt);
}

void 
CutSceneCamera::LateUpdate(const FLOAT& dt)
{
	delta += dt;
	switch (index)
	{
	case CUTSCENE_PLAYERDEAD: {break; }
	case CUTSCENE_BOSSSPAWN: 
	{
		if (delta < 3)
		{
			LookAtBoss();
		}
		else
		{
			delta = 0;
			index = CUTSCENE_NONE;
		}
		break; 
	}
	case CUTSCENE_BOSSDEAD: {break; }
	case CUTSCENE_NONE: {break; }
	default:
		break;
	}

	D3DXMATRIX im;
	D3DXMatrixIdentity(&im);
	D3DXMatrixInverse(&im, NULL, &transform->worldMatrix);
	camera->SetViewMatrix(im);
	camera->Render(dt);
	GameObject::LateUpdate(dt);
}

void 
CutSceneCamera::Render(const FLOAT& dt)
{
	GameObject::Render(dt);
}

void 
CutSceneCamera::Free(void)
{
	GameObject::Free();
}
