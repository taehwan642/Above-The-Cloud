#include "DXUT.h"
#include "../Engine/Transform.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/StaticMesh.h"
#include "../Engine/ObjectManager.h"
#include "../Engine/Shader.h"
#include "../Engine/RenderManager.h"
#include "Sea.h"

Sea::Sea(void)
{
	transform = new Engine::Transform();
	transform->position = { 0,-50,0 };
	transform->scale = { 10,1,10 };
	componentgroup.emplace(L"Transform", transform);
	mesh = dynamic_cast<Engine::StaticMesh*>(Engine::ResourceManager::GetInstance()->LoadResource(L"Sea"));
	componentgroup.emplace(L"Mesh", mesh);
	shader = dynamic_cast<Engine::Shader*>(Engine::ResourceManager::GetInstance()->LoadResource(L"defaultShader"));
	componentgroup.emplace(L"Shader", shader);
}

Sea::~Sea(void)
{
}

INT Sea::Update(const FLOAT& dt)
{
	GameObject::Update(dt);
	Engine::RenderManager::GetInstance()->AddRenderObject(ID_NORMALMESH, this);
	return OBJALIVE;
}

void Sea::LateUpdate(const FLOAT& dt)
{
	GameObject::LateUpdate(dt);
}

void Sea::Render(const FLOAT& dt)
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

	GameObject::Render(dt);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void Sea::Free(void)
{
	GameObject::Free();
}
