#include "DXUT.h"
#include "../Engine/Transform.h"
#include "../Engine/SubjectManager.h"
#include "../Engine/Singleton.h"
#include "PlayerObserver.h"
#include "../Engine/Camera.h"
#include "PlaneCamera.h"

PlaneCamera::PlaneCamera(void)
{
	InitCamera();
}

PlaneCamera::~PlaneCamera(void)
{
}

void PlaneCamera::InitCamera(void)
{
	transform = new Engine::Transform();
	targetTransform = new Engine::Transform();
	camera = new Engine::Camera();
	componentgroup.emplace(L"Transform", transform);
	componentgroup.emplace(L"TargetTransform", targetTransform);
	componentgroup.emplace(L"Camera", camera);

	targetTransform->localPosition = { 0, 250, 0 };

	observer = new PlayerObserver();
	Engine::SubjectManager::GetInstance()->Subscribe(observer);
	Engine::SubjectManager::GetInstance()->Notify(static_cast<UINT>(PlayerInfos::PLAYERTRANSFORM));
	Engine::SubjectManager::GetInstance()->Notify(static_cast<UINT>(PlayerInfos::PLAYERDEAD));

	targetTransform->SetParent(observer->GetTransform());

	transform->curQuaternion = D3DXQUATERNION(0, 1, 0, 0);

	camera->SetProjectionMatrix(D3DXToRadian(70),
		static_cast<float>(DXUTGetD3D9BackBufferSurfaceDesc()->Width) /
		static_cast<float>(DXUTGetD3D9BackBufferSurfaceDesc()->Height),
		0.01, 50000);
}

INT PlaneCamera::Update(const FLOAT& dt)
{
	if (DXUTWasKeyPressed('C'))
	{
		lookback = !lookback;
		cameraDistance *= -1.0f;
	}

	if (observer->GetIsPlayerDead() == false)
	{
		D3DXVECTOR3 look = *D3DXVec3Normalize(&D3DXVECTOR3(), reinterpret_cast<D3DXVECTOR3*>(&targetTransform->worldMatrix._31));
		D3DXVECTOR3 position = targetTransform->worldPosition;

		transform->localPosition = position + look * cameraDistance;

		look *= -1.f;

		D3DXVECTOR3 right;
		D3DXVec3Normalize(&right, reinterpret_cast<D3DXVECTOR3*>(&observer->GetTransform()->worldMatrix._11));

		right *= -1.f;

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
	else
	{
		D3DXVECTOR3 playerlook = observer->GetTransform()->localPosition - transform->localPosition;
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

	GameObject::Update(dt);
	return OBJALIVE;
}

void PlaneCamera::LateUpdate(const FLOAT& dt)
{
	D3DXMATRIX matView;
	if (observer->GetIsPlayerDead() == false && lookback)
	{
		D3DXVECTOR3 reverse = -(*reinterpret_cast<D3DXVECTOR3*>(&transform->worldMatrix._31));
		memcpy(&transform->worldMatrix._31, reverse, sizeof(D3DXVECTOR3));
	}
	
	D3DXMatrixInverse(&matView, 0, &transform->worldMatrix);
	
	camera->SetViewMatrix(matView);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	worldCameraPosition = D3DXVECTOR4(transform->localPosition, 1);
	camera->Render(dt);
	GameObject::LateUpdate(dt);
}

void PlaneCamera::Render(const FLOAT& dt)
{
	GameObject::Render(dt);
}

void PlaneCamera::Free(void)
{
	Engine::SubjectManager::GetInstance()->UnSubscribe(observer);
	observer->Release();
	GameObject::Free();
}
