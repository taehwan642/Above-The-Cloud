#include "DXUT.h"
#include "../Engine/SubjectManager.h"
#include "PlayerObserver.h"
#include "../Engine/Transform.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/StaticMesh.h"
#include "../Engine/ObjectManager.h"
#include "../Engine/Collider.h"
#include "../Engine/CollisionManager.h"
#include "../Engine/Shader.h"
#include "testChild.h"

testChild::testChild(void)
{
	observer = new PlayerObserver();
	Engine::SubjectManager::GetInstance()->Subscribe(observer);
	Engine::SubjectManager::GetInstance()->Notify(static_cast<UINT>(PlayerInfos::PLAYERTRANSFORM));
	
	testshader = dynamic_cast<Engine::Shader*>(Engine::ResourceManager::GetInstance()->LoadResource(L"dyshader"));
	
	t = new Engine::Transform(/*observer->GetTransform()*/);
	componentgroup.emplace(L"Transform", t);
	componentgroup.emplace(L"Shader", testshader);
	t->scale = D3DXVECTOR3(0.1f, 0.1f, 0.1f);
	t->position = { 5,5,50 };
	testsphere = dynamic_cast<Engine::StaticMesh*>(Engine::ResourceManager::GetInstance()->LoadResource(L"Cloud"));
	componentgroup.emplace(L"StaticMesh", testsphere);
	collider = new Engine::Collider(2, &t->position);
	componentgroup.emplace(L"collider", collider);
	Engine::CollisionManager::GetInstance()->PushData(MONSTER, this);

	colliderdata.center = &t->position;
	colliderdata.radius = 1;
	colliderdata.tag = L"player";
	colliderdata.ishit = false;
}

testChild::~testChild(void)
{
}

void testChild::CollisionEvent(const wstring& _objectTag, GameObject* _gameObject)
{
	if (_objectTag == L"PlayerShoot")
	{
		cout << "마우스로 처맞음" << endl;
	}
}

INT testChild::Update(const float& dt)
{
	GameObject::Update(dt);
	return OBJALIVE;
}

void testChild::LateUpdate(const FLOAT& dt)
{
	GameObject::LateUpdate(dt);
}

void testChild::Render(const FLOAT& dt)
{
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	testshader->SetupTable(t->worldMatrix);

	UINT pass = 0;
	LPD3DXEFFECT tempeffect = testshader->GetEffect();
	tempeffect->Begin(&pass, 0);
	tempeffect->BeginPass(0);
	testsphere->RenderMesh(tempeffect);
	tempeffect->EndPass();
	tempeffect->End();

	collider->RenderCollider();
	GameObject::Render(dt);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void testChild::Free(void)
{
	Engine::SubjectManager::GetInstance()->UnSubscribe(observer);
	observer->Release();
	GameObject::Free();
}
