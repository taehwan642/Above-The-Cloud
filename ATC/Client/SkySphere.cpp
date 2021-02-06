#include "DXUT.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/StaticMesh.h"
#include "../Engine/Shader.h"
#include "../Engine/Transform.h"
#include "SkySphere.h"

SkySphere::SkySphere(void)
{
	transform = new Engine::Transform();
	transform->scale = { 1.7,1.7,1.7 };
	componentgroup.emplace(L"Transform", transform);
	skysphere = dynamic_cast<Engine::StaticMesh*>(Engine::ResourceManager::GetInstance()->LoadResource(L"SkySphere"));
	componentgroup.emplace(L"StaticMesh", skysphere);
	shader = dynamic_cast<Engine::Shader*>(Engine::ResourceManager::GetInstance()->LoadResource(L"defaultShader"));
	componentgroup.emplace(L"Shader", shader);
}

SkySphere::~SkySphere(void)
{
}

INT SkySphere::Update(const float& dt)
{
	GameObject::Update(dt);
	return OBJALIVE;
}

void SkySphere::LateUpdate(const FLOAT& dt)
{
	GameObject::LateUpdate(dt);
}

void SkySphere::Render(const FLOAT& dt)
{
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	
	shader->SetupTable(transform->worldMatrix);
	LPD3DXEFFECT effect = shader->GetEffect();
	UINT pass;
	effect->Begin(&pass, 0);
	effect->BeginPass(0);
	skysphere->RenderMesh();
	effect->EndPass();
	effect->End();
	GameObject::Render(dt);
}

void SkySphere::Free(void)
{
	GameObject::Free();
}
