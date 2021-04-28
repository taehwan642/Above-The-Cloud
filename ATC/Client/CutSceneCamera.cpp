#include "DXUT.h"
#include "../Engine/Camera.h"
#include "../Engine/Transform.h"
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
	case CUTSCENE_PLAYERDEAD: {break; }
	case CUTSCENE_BOSSSPAWN: {break; }
	case CUTSCENE_BOSSDEAD: {break; }
	default:
		break;
	}
	// 1. MonsterObserver에 위치 받아서
	// 2. 보스인지 확인하고
	// 3. 보스라면 그 위치 주소 받아서 바라보게 하기
	// 4. 시간이 지나면 다시 연출 끝났다고 플래그 세우기
	//D3DXVECTOR3 playerlook = observer->GetTransform()->localPosition - transform->localPosition;
	//D3DXVec3Normalize(&playerlook, &playerlook);
	//
	//D3DXVECTOR3 right;
	//D3DXVec3Cross(&right, &D3DXVECTOR3(0, 1, 0), &playerlook);
	//D3DXVec3Normalize(&right, &right);
	//
	//D3DXVECTOR3 up;
	//D3DXVec3Cross(&up, &playerlook, &right);
	//D3DXVec3Normalize(&up, &up);
	//
	//D3DXMATRIX matRot;
	//D3DXMatrixIdentity(&matRot);
	//memcpy(&matRot._11, &right, sizeof(D3DXVECTOR3));
	//memcpy(&matRot._21, &up, sizeof(D3DXVECTOR3));
	//memcpy(&matRot._31, &playerlook, sizeof(D3DXVECTOR3));
	//D3DXQuaternionRotationMatrix(&transform->quaternion, &matRot);

	D3DXMATRIX im;
	D3DXMatrixIdentity(&im);
	D3DXMatrixTranslation(&im, 0, 0, 62);
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
