#include "DXUT.h"
#include "../Engine/Transform.h"
#include "../Engine/RenderManager.h"
#include "RadarDot.h"
#include "../Engine/ObjectManager.h"
#include "../Engine/SubjectManager.h"
#include "PlayerObserver.h"
#include "MonsterInfoManager.h"
#include "MonsterBase.h"
#include "RadarPlane.h"

// 스텐실 버퍼로 한번 해보기.

RadarPlane::RadarPlane(void) :
	StaticUI(L"RadarPlane")
{
	transform->localPosition = { 1150, 600 , 0 };
	middledot = Engine::ObjectManager::GetInstance()->CheckActiveFalsedObjectAndSpawn<RadarDot>(UI, L"RadarDot");
	middledot->SetPosition(transform->localPosition);

	observer = new PlayerObserver();
	Engine::SubjectManager::GetInstance()->Subscribe(observer);
	Engine::SubjectManager::GetInstance()->Notify(static_cast<UINT>(PlayerInfos::PLAYERTRANSFORM));
}

RadarPlane::~RadarPlane(void)
{
}

INT RadarPlane::Update(const FLOAT& dt)
{
	for (auto& const v : dotpositions)
		v.first->SetActive(false);
	dotpositions.clear();

	//D3DXVECTOR3 dir = -(*reinterpret_cast<D3DXVECTOR3*>(&observer->GetTransform()->worldMatrix._31));
	//D3DXVec3Normalize(&dir, &dir);
	//static float yaw = 0;
	//yaw += dt * 2;
	//D3DXMATRIX r;
	//D3DXMatrixRotationQuaternion(&r, &observer->GetTransform()->curQuaternion);
	//D3DXVECTOR3 rot = Engine::Transform::rotationMatrixToEulerAngles(r);
	//D3DXQuaternionRotationYawPitchRoll(&transform->quaternion, 0, 0, yaw);

	for (int i = 0; i < MONSTEREND; ++i)
	{
		for (auto& v : MonsterInfoManager::GetInstance()->GetListWithMonsterType(static_cast<MonsterType>(i)))
		{
			Engine::Transform* t = dynamic_cast<Engine::Transform*>(v->GetComponent(L"Transform"));
			D3DXVECTOR3 mpos = t->localPosition;
			D3DXVECTOR3 vec = observer->GetTransform()->localPosition - mpos;

			RadarDot* d = Engine::ObjectManager::GetInstance()->CheckActiveFalsedObjectAndSpawn<RadarDot>(UI, L"RadarDot");
			d->SetActive(true); // 이걸 안해주면 activefalse된 첫번째 애를 넘겨주기에 같은 값을 받아오게 됨.
			//Engine::Transform* dotT = dynamic_cast<Engine::Transform*>(d->GetComponent(L"Transform"));
			//
			//D3DXVec3TransformNormal(
			//	&dotT->localPosition,
			//	&dotT->localPosition,
			//	&transform->worldMatrix);

			////d->ActiveTrue(transform);
			//D3DXVECTOR3 res = vec + dotT->localPosition;
			
			dotpositions.emplace_back(d, vec);
		}
	}

	for (const auto& pos : dotpositions)
	{
		D3DXVECTOR3 result = { transform->localPosition.x + pos.second.x,
							   transform->localPosition.y + pos.second.z,
							   transform->localPosition.z };
		pos.first->SetPosition(result);
	}

	Engine::RenderManager::GetInstance()->AddRenderObject(ID_UI, this);
	return StaticUI::Update(dt);
}

void RadarPlane::LateUpdate(const FLOAT& dt)
{
	StaticUI::LateUpdate(dt);
}

void RadarPlane::Render(const FLOAT& dt)
{
	StaticUI::Render(dt);
}

void RadarPlane::Free(void)
{
	for (int i = 0; i < dotpositions.size(); ++i)
		dotpositions.at(i).first->Release();
	Engine::SubjectManager::GetInstance()->UnSubscribe(observer);
	observer->Release();
	StaticUI::Free();
}
