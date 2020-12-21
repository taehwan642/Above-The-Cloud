#include "DXUT.h"
#include "../Engine/Transform.h"
#include "../Engine/StaticMesh.h"
#include "../Engine/ResourceManager.h"
#include "test.h"

test::test(void)
{
	testMesh = dynamic_cast<Engine::StaticMesh*>(Engine::ResourceManager::GetInstance()->LoadResource(L"test"));
	componentgroup.emplace(L"test", testMesh);
	transform = new Engine::Transform();
	componentgroup.emplace(L"Transform", transform);
}

test::~test(void)
{
}

void test::Update(const float& dt)
{
	if (DXUTIsKeyDown('A'))
	{
		transform->position.x -= 0.1f;
	}
	if (DXUTIsKeyDown('D'))
	{
		transform->position.x += 0.1f;
	}
	if (DXUTIsKeyDown('W'))
	{
		transform->position.z += 0.1f;
	}
	if (DXUTIsKeyDown('S'))
	{
		transform->position.z -= 0.1f;
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
	testMesh->RenderMesh();
	GameObject::Render();
}

void test::Free(void)
{
	GameObject::Free();
}
