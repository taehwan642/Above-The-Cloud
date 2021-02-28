#include "DXUT.h"
#include "../Engine/Transform.h"
#include "../Engine/SubjectManager.h"
#include "../Engine/Singleton.h"
#include "PlayerObserver.h"
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
	componentgroup.emplace(L"Transform", transform);
	componentgroup.emplace(L"TargetTransform", targetTransform);

	targetTransform->position = { 0, 250, 0 };

	observer = new PlayerObserver();
	Engine::SubjectManager::GetInstance()->Subscribe(observer);
	Engine::SubjectManager::GetInstance()->Notify(static_cast<UINT>(PlayerInfos::PLAYERTRANSFORM));
	Engine::SubjectManager::GetInstance()->Notify(static_cast<UINT>(PlayerInfos::PLAYERDEAD));

	targetTransform->SetParent(observer->GetTransform());

	transform->curQuaternion = D3DXQUATERNION(0, 1, 0, 0);
}

bool targetplane = true;

INT PlaneCamera::Update(const FLOAT& dt)
{
	if (DXUTWasKeyPressed('C'))
	{
		lookback = !lookback;
		cameraDistance *= -1.0f;
	}

	if (DXUTWasKeyPressed('V'))
	{
		targetplane = !targetplane;
	}

	if (observer->GetIsPlayerDead() == false)
	{
		D3DXVECTOR3 look = *D3DXVec3Normalize(&D3DXVECTOR3(), reinterpret_cast<D3DXVECTOR3*>(&targetTransform->worldMatrix._31));
		D3DXVECTOR3 position = *reinterpret_cast<D3DXVECTOR3*>(&targetTransform->worldMatrix._41);

		transform->position = position + look * cameraDistance;

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
		// Go Back
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
	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj,
		D3DXToRadian(70),
		static_cast<float>(DXUTGetD3D9BackBufferSurfaceDesc()->Width) /
		static_cast<float>(DXUTGetD3D9BackBufferSurfaceDesc()->Height),
		0.01, 50000);
	if(targetplane)
		DEVICE->SetTransform(D3DTS_VIEW, &matView);
	else
	{
		D3DXMATRIX im;
		D3DXMatrixIdentity(&im);
		D3DXMatrixTranslation(&im, 0, 0, 62);
		DEVICE->SetTransform(D3DTS_VIEW, &im);
	}
	DEVICE->SetTransform(D3DTS_PROJECTION, &matProj);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	worldCameraPosition = D3DXVECTOR4(transform->position, 1);

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
