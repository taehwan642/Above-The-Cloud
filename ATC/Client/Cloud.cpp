#include "DXUT.h"
#include "../Engine/Transform.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/StaticMesh.h"
#include "../Engine/ObjectManager.h"
#include "../Engine/Collider.h"
#include "../Engine/CollisionManager.h"
#include "../Engine/Shader.h"
#include "Cloud.h"

Cloud::Cloud(void)
{
	shader = dynamic_cast<Engine::Shader*>(Engine::ResourceManager::GetInstance()->LoadResource(L"dyshader"));
	transform = new Engine::Transform(/*observer->GetTransform()*/);
	componentgroup.emplace(L"Transform", transform);
	componentgroup.emplace(L"Shader", shader);
	transform->scale = D3DXVECTOR3(0.1f, 0.1f, 0.1f);
	transform->position = { 5,5,50 };
	mesh = dynamic_cast<Engine::StaticMesh*>(Engine::ResourceManager::GetInstance()->LoadResource(L"Cloud"));
	componentgroup.emplace(L"StaticMesh", mesh);
	collider = new Engine::Collider(2, &transform->position);
	componentgroup.emplace(L"collider", collider);
	Engine::CollisionManager::GetInstance()->PushData(INTERACTIVEOBJ, this);

	colliderdata.center = &transform->position;
	colliderdata.radius = 1;
	colliderdata.tag = L"Cloud";
}

Cloud::~Cloud(void)
{
}

void Cloud::CollisionEvent(const std::wstring& _objectTag, GameObject* _gameObject)
{
	if (_objectTag == L"PlayerShoot")
	{
		
	}
}

INT Cloud::Update(const float& dt)
{
	GameObject::Update(dt);
	return OBJALIVE;
}

void Cloud::LateUpdate(const FLOAT& dt)
{
	GameObject::LateUpdate(dt);
}

void Cloud::Render(const FLOAT& dt)
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

void Cloud::Free(void)
{
	GameObject::Free();
}
