#include "DXUT.h"
#include "../Engine/Camera.h"
#include "../Engine/Transform.h"
#include "MonsterInfoManager.h"
#include "PlayerObserver.h"
#include "../Engine/SubjectManager.h"
#include "MonsterBase.h"
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

	observer = new PlayerObserver();
	Engine::SubjectManager::GetInstance()->Subscribe(observer);
	Engine::SubjectManager::GetInstance()->Notify(static_cast<UINT>(PlayerInfos::PLAYERTRANSFORM));
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
CutSceneCamera::LookAt(const D3DXVECTOR3& _look)
{
	D3DXVECTOR3 look = _look;// = t->localPosition - transform->localPosition;
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
}

void
CutSceneCamera::LookAtBoss(void)
{
	// 1. MonsterObserver에 위치 받아서
	std::list<MonsterBase*> list = MonsterInfoManager::GetInstance()->GetListWithMonsterType(BOSS);
	// 2. 보스인지 확인하고
	// 3. 보스라면 그 위치 주소 받아서 바라보게 하기
	if (list.size() != 0)
	{
		MonsterBase* m = (*list.begin()); // 보스는 오로지 하나만 존재하기에.
		Engine::Transform* t = dynamic_cast<Engine::Transform*>(m->GetComponent(L"Transform"));
		//std::cout << "LIST : " << t->localPosition.x << " " << t->localPosition.y << " " << t->localPosition.z << " " << std::endl;
		// 위 테스트 만족.
		// 4. 시간이 지나면 다시 연출 끝났다고 플래그 세우기
		LookAt(t->localPosition - transform->localPosition);
	}
	else
	{
		index = CUTSCENE_NONE;
	}
}

void CutSceneCamera::LookAtPlane(void)
{
	LookAt(observer->GetTransform()->localPosition - transform->localPosition);
}

INT 
CutSceneCamera::Update(const FLOAT& dt)
{
	return GameObject::Update(dt);
}

void 
CutSceneCamera::LateUpdate(const FLOAT& dt)
{

	switch (index)
	{
	case CUTSCENE_PLAYERDEAD: 
	{
		delta += dt;
		if (delta < 3)
		{
			LookAtPlane();
		}
		else
		{
			delta = 0;
			index = CUTSCENE_NONE;
		}
		break; 
	}
	case CUTSCENE_BOSSSPAWN: 
	case CUTSCENE_BOSSDEAD: 
	{
		delta += dt;
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
	Engine::SubjectManager::GetInstance()->UnSubscribe(observer);
	observer->Release();
	GameObject::Free();
}
