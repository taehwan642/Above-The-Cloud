#include "DXUT.h"
#include "../Engine/Transform.h"
#include "../Engine/SubjectManager.h"
#include "PlayerObserver.h"
#include "Camera.h"

Camera::Camera(void)
{
	transform = new Engine::Transform();
	componentgroup.emplace(L"Transform", transform);
	transform->position = { 0,282, 905 };
	observer = new PlayerObserver();
	Engine::SubjectManager::GetInstance()->Subscribe(observer);
	Engine::SubjectManager::GetInstance()->Notify(static_cast<UINT>(PlayerInfos::PLAYERTRANSFORM));
	transform->SetParent(observer->GetTransform());
}

Camera::~Camera(void)
{
}

void Camera::Update(const float& dt)
{
	if (DXUTWasKeyPressed('O'))
	{
		lookback = !lookback;
		transform->position.z = -transform->position.z;
	}

	//D3DXVec3TransformCoord(&transform->position, &D3DXVECTOR3(0,282,905), &observer->GetTransform()->worldMatrix);
	//(&transform->curQuaternion, &transform->curQuaternion, &observer->GetTransform()->curQuaternion, dt * 3);
	GameObject::Update(dt);
}

void Camera::LateUpdate(const FLOAT& dt)
{
	//DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//1. Temp World 하나 생성
	//2. 그 월드를 카메라가 lerp로 천천히 따라가기
	
	D3DXMATRIX matView;
	if (!lookback)
	{
		D3DXVECTOR3 reverse = -(*reinterpret_cast<D3DXVECTOR3*>(&transform->worldMatrix._31));
		memcpy(&transform->worldMatrix._31, reverse, sizeof(D3DXVECTOR3));
	}
	
	/*D3DXVECTOR3 oblook, obright, obup;
	obright = *reinterpret_cast<D3DXVECTOR3*>(&observer->GetTransform()->worldMatrix._11);
	obup = *reinterpret_cast<D3DXVECTOR3*>(&observer->GetTransform()->worldMatrix._21);
	oblook = *reinterpret_cast<D3DXVECTOR3*>(&observer->GetTransform()->worldMatrix._31);
	
	transform->worldMatrix *= *D3DXMatrixScaling(&D3DXMATRIX(),
		observer->GetTransform()->scale.x,
		observer->GetTransform()->scale.y,
		observer->GetTransform()->scale.z);
	
	D3DXVECTOR3 look, right, up;
	right = *reinterpret_cast<D3DXVECTOR3*>(&transform->worldMatrix._11);
	up = *reinterpret_cast<D3DXVECTOR3*>(&transform->worldMatrix._21);
	look = *reinterpret_cast<D3DXVECTOR3*>(&transform->worldMatrix._31);

	D3DXVec3Lerp(&right, &right, &obright, dt * 10);
	D3DXVec3Lerp(&up, &up, &obup, dt * 10);
	D3DXVec3Lerp(&look, &look, &oblook, dt * 10);

	memcpy(&transform->worldMatrix._11, right, sizeof(D3DXVECTOR3));
	memcpy(&transform->worldMatrix._21, up, sizeof(D3DXVECTOR3));
	memcpy(&transform->worldMatrix._31, look, sizeof(D3DXVECTOR3));

	transform->worldMatrix *= *D3DXMatrixTranslation(&D3DXMATRIX(), 
		observer->GetTransform()->position.x, 
		observer->GetTransform()->position.y, 
		observer->GetTransform()->position.z);*/

	D3DXMatrixInverse(&matView, 0, &transform->worldMatrix);
	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj,
		D3DXToRadian(70),
		static_cast<float>(DXUTGetD3D9BackBufferSurfaceDesc()->Width) /
		static_cast<float>(DXUTGetD3D9BackBufferSurfaceDesc()->Height),
		0.01, 50000);
	DEVICE->SetTransform(D3DTS_VIEW, &matView);
	DEVICE->SetTransform(D3DTS_PROJECTION, &matProj);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	GameObject::LateUpdate(dt);
}

void Camera::Render(const FLOAT& dt)
{
	GameObject::Render(dt);
}

void Camera::Free(void)
{
	GameObject::Free();
}
