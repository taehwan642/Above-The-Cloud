#include "DXUT.h"
#include "../Engine/Transform.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/StaticMesh.h"
#include "../Engine/CollisionManager.h"
#include "../Engine/Collider.h"
#include "../Engine/Trail.h"
#include "../Engine/SubjectManager.h"
#include "PlayerObserver.h"
#include "Missile.h"

Missile::Missile(void)
{
	transform = new Engine::Transform();
	componentgroup.emplace(L"transform", transform);
	//mesh = dynamic_cast<Engine::StaticMesh*>(Engine::ResourceManager::GetInstance()->LoadResource(L"Missile"));
	collider = new Engine::Collider(1, &transform->position, ObjectTag::PLAYER);
	Engine::CollisionManager::GetInstance()->PushData(MISSILE, this);
	componentgroup.emplace(L"collider", collider);
	D3DXCreateSphere(DEVICE, 5, 20, 20, &test, nullptr);

	ob = new PlayerObserver();
	Engine::SubjectManager::GetInstance()->Subscribe(ob);
	Engine::SubjectManager::GetInstance()->Notify(static_cast<UINT>(PlayerInfos::PLAYERTRANSFORM));

	transform->position = ob->GetTransform()->position;
	
	memcpy(&transform->worldMatrix._11, &ob->GetTransform()->worldMatrix._11, sizeof(D3DXVECTOR3));
	memcpy(&transform->worldMatrix._21, &ob->GetTransform()->worldMatrix._21, sizeof(D3DXVECTOR3));
	memcpy(&transform->worldMatrix._31, &ob->GetTransform()->worldMatrix._31, sizeof(D3DXVECTOR3));

	transform->quaternion = ob->GetTransform()->quaternion;
	transform->curQuaternion = ob->GetTransform()->curQuaternion;
}

Missile::~Missile(void)
{

}

void Missile::Update(const FLOAT& dt)
{
	ob->GetTransform();

	// 나와 플레이어의 방향을 구한다.
	// 내 forward와 내적한다.
	D3DXVECTOR3 look = D3DXVECTOR3(5, 5, 50) - transform->position;
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
	transform->position += dir  * 20 * dt;
	GameObject::Update(dt);
}

void Missile::LateUpdate(const FLOAT& dt)
{
	// ob에서 받아온 그 록 몬스터의 포인터를 받아옴
	// 그 몬스터의 위치에 pos에 받아서
	// x = z,y
	// y = x,z
	// z = y,x
	// rotate look z, up y, right x
	// RAY & SPHERE
	// 다른 모든 적들은 어떻게 불러오나?
	// 그냥 하나의 플레이어의 forward를 받아서 하는게 낫겠다.
	// 그럼 모든 적들이 플레이어의 obesrver를 가지면 되고,
	// 따로 또 Observer 만들어서 UI데이터 넣어줄 수 있게 만들면 끝나겠네
	// 플레이어와 다른 모든 적들과 내적해서, 플레이어의 forward와 가장 가까운 적에게 lock를 건다.
	// 그러려면, 일단 move를 lock시키고 최소한의 내적 범위를 알아내야함. (화면 밖에있는것들은 lock잡으면 안되니까)
	
	
	

	
	GameObject::LateUpdate(dt);
}

void Missile::Render(const FLOAT& dt)
{
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	DEVICE->SetTransform(D3DTS_WORLD, &transform->worldMatrix);
	test->DrawSubset(0);
	collider->RenderCollider();
	GameObject::Render(dt);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void Missile::Free(void)
{
	GameObject::Free();
}
