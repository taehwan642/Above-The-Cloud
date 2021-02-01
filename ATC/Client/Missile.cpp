#include "DXUT.h"
#include "../Engine/Transform.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/StaticMesh.h"
#include "../Engine/CollisionManager.h"
#include "../Engine/Collider.h"
#include "../Engine/Trail.h"
#include "../Engine/SubjectManager.h"
#include "../Engine/Shader.h"
#include "PlayerObserver.h"
#include "Missile.h"

Missile::Missile(void)
{
	transform = new Engine::Transform();
	componentgroup.emplace(L"Transform", transform);
	mesh = dynamic_cast<Engine::StaticMesh*>(Engine::ResourceManager::GetInstance()->LoadResource(L"Missile"));
	
	shader = dynamic_cast<Engine::Shader*>(Engine::ResourceManager::GetInstance()->LoadResource(L"dyshader"));

	collider = new Engine::Collider(1, &transform->position);
	colliderdata.center = &transform->position;
	colliderdata.ishit = false;
	colliderdata.radius = 1;
	colliderdata.tag = L"Missile";

	Engine::CollisionManager::GetInstance()->PushData(MISSILE, this);
	componentgroup.emplace(L"collider", collider);

	transform->scale = { 0.02f, 0.02f, 0.02f };

	ob = new PlayerObserver();
	Engine::SubjectManager::GetInstance()->Subscribe(ob);
	Engine::SubjectManager::GetInstance()->Notify(static_cast<UINT>(PlayerInfos::PLAYERTRANSFORM));
	Engine::SubjectManager::GetInstance()->Notify(static_cast<UINT>(PlayerInfos::PLAYERMISSILELOCKOBJECT));

	transform->position = ob->GetTransform()->position;
	
	D3DXVECTOR3 vec;
	vec = *reinterpret_cast<D3DXVECTOR3*>(&ob->GetTransform()->worldMatrix._11);
	vec *= -1.f;
	memcpy(&transform->worldMatrix._11, &vec, sizeof(D3DXVECTOR3));
	vec = *reinterpret_cast<D3DXVECTOR3*>(&ob->GetTransform()->worldMatrix._21);
	vec *= -1.f;
	memcpy(&transform->worldMatrix._21, &vec, sizeof(D3DXVECTOR3));
	vec = *reinterpret_cast<D3DXVECTOR3*>(&ob->GetTransform()->worldMatrix._31);
	vec *= -1.f;
	memcpy(&transform->worldMatrix._31, &vec, sizeof(D3DXVECTOR3));
	
	// 1. Player의 forward로 간다
	transform->quaternion = ob->GetTransform()->quaternion;
	transform->curQuaternion = ob->GetTransform()->curQuaternion;

	transform->Rotate(Engine::Transform::UP, D3DXToRadian(180));

	trail = new Engine::Trail();
	trail->Initalize(&transform->worldMatrix, 1024, 0.03f, 4, 3, L"TrailTexture");
	componentgroup.emplace(L"Trail", trail);
	// 근데 씨바 ㄹ왜 반대로 갈까?
	// 반대로 가는 이유 1. player (ob)의 dir은 원래 반대여야만 한다.
	// 2. 시간이 되면 유도 시작
}

Missile::~Missile(void)
{

}

void Missile::Update(const FLOAT& dt)
{
	//-36
	D3DXVECTOR3 trailpos[2];
	D3DXVec3TransformCoord(&trailpos[0], &D3DXVECTOR3(-2, 0, -36), &transform->worldMatrix);
	D3DXVec3TransformCoord(&trailpos[1], &D3DXVECTOR3(2, 0, -36), &transform->worldMatrix);

	trail->AddNewTrail(trailpos[0], trailpos[1], dt);

	if (ob->GetMissileLock() != nullptr && homingtime <= 0)
	{
		D3DXVECTOR3 dstPos = 
			dynamic_cast<Engine::Transform*>
			(ob->GetMissileLock()->GetComponent(L"Transform"))->position;
		// 나와 플레이어의 방향을 구한다.
		// 내 forward와 내적한다.
		D3DXVECTOR3 look = dstPos - transform->position;
		D3DXVec3Normalize(&look, &look);
		//look *= -1.f;
	
		//  up과 look외적 => right
		D3DXVECTOR3 right;
		D3DXVec3Cross(&right, &D3DXVECTOR3(0, 1, 0), &look);
		D3DXVec3Normalize(&right, &right);
	
		//right *= -1.f;
	
		// look과 right 외적 => up
		D3DXVECTOR3 up;
		D3DXVec3Cross(&up, &look, &right);
		D3DXVec3Normalize(&up, &up);
	
		D3DXMATRIX matRot;
		D3DXMatrixIdentity(&matRot);
		memcpy(&matRot._11, &right, sizeof(D3DXVECTOR3));
		memcpy(&matRot._21, &up, sizeof(D3DXVECTOR3));
		memcpy(&matRot._31, &look, sizeof(D3DXVECTOR3));
		D3DXQuaternionRotationMatrix(&transform->quaternion, &matRot);
		D3DXVECTOR3 dir = *reinterpret_cast<D3DXVECTOR3*>(&transform->worldMatrix._31);
		D3DXVec3Normalize(&dir, &dir);
		transform->position += dir * 40 * dt;
	}
	else
	{
		homingtime -= dt;
		D3DXVECTOR3 dir = *reinterpret_cast<D3DXVECTOR3*>(&transform->worldMatrix._31);
		D3DXVec3Normalize(&dir, &dir);
		transform->position += dir * 20 * dt;
	}
	
	GameObject::Update(dt);
}

void Missile::LateUpdate(const FLOAT& dt)
{
	Engine::SubjectManager::GetInstance()->Notify(static_cast<UINT>(PlayerInfos::PLAYERMISSILELOCKOBJECT));
	GameObject::LateUpdate(dt);
}

void Missile::Render(const FLOAT& dt)
{
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	shader->SetupTable(transform->worldMatrix);
	UINT pass = 0;
	LPD3DXEFFECT tempeffect = shader->GetEffect();
	tempeffect->Begin(&pass, 0);
	tempeffect->BeginPass(0);
	mesh->RenderMesh(tempeffect);
	tempeffect->EndPass();
	tempeffect->End();
	//collider->RenderCollider();
	
	GameObject::Render(dt);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void Missile::Free(void)
{
	GameObject::Free();
}
