#include "DXUT.h"
#include "../Engine/Transform.h"
#include "../Engine/StaticMesh.h"
#include "../Engine/DynamicMesh.h"
#include "../Engine/Shader.h"
#include "../Engine/ResourceManager.h"
#include "test.h"

test::test(void)
{
	testshader = dynamic_cast<Engine::Shader*>(Engine::ResourceManager::GetInstance()->LoadResource(L"dyshader"));
	testMesh = dynamic_cast<Engine::StaticMesh*>(Engine::ResourceManager::GetInstance()->LoadResource(L"test"));
	testdynamic = dynamic_cast<Engine::DynamicMesh*>(Engine::ResourceManager::GetInstance()->LoadResource(L"dynamic"));
	componentgroup.emplace(L"shader", testshader);
	transform = new Engine::Transform();
	componentgroup.emplace(L"Transform", transform);
	
	testdynamic->SetParent(&transform->worldMatrix);
	
	UINT aniset = 0;
	testdynamic->SetAnimationSet(aniset);

	transform->position.z = 0;
}

test::~test(void)
{
}

void test::Update(const float& dt)
{
	if (DXUTIsKeyDown('E'))
		transform->rotation.y += 2 * dt;
	if (DXUTIsKeyDown('Q'))
		transform->rotation.y -= 2 * dt;
	if (DXUTIsKeyDown('A'))
	{
		transform->position.x -= 300 * dt;
	}
	if (DXUTIsKeyDown('D'))
	{
		transform->position.x += 300 * dt;
	}
	if (DXUTIsKeyDown('W'))
	{
		transform->position.z += 300 * dt;
	}
	if (DXUTIsKeyDown('S'))
	{
		transform->position.z -= 300 * dt;
	}
	GameObject::Update(dt);
}

void test::LateUpdate(void)
{
	DEVICE->SetTransform(D3DTS_WORLD, &transform->worldMatrix);
	GameObject::LateUpdate();
}

void test::Render(void)
{
	//testshader->SetupTable();
	//LPD3DXEFFECT tempeffect = testshader->GetEffect();
	//UINT pass = 0;
	//tempeffect->Begin(&pass, 0);
	//tempeffect->BeginPass(0);
	testdynamic->PlayAnimation(DXUTGetElapsedTime());
	testdynamic->RenderNoSkinnedMesh();
	//testMesh->RenderMesh(tempeffect);
	//tempeffect->EndPass();
	//tempeffect->End();
	GameObject::Render();
}

void test::Free(void)
{
	GameObject::Free();
}
