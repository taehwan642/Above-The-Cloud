#include "DXUT.h"
#include "../Engine/Transform.h"
#include "../Engine/StaticMesh.h"
#include "../Engine/ResourceManager.h"
#include "test.h"

test::test(void)
{
}

test::~test(void)
{
}

void test::Update(const float& dt)
{
	GameObject::Update(dt);
}

void test::LateUpdate(void)
{
	GameObject::LateUpdate();
}

void test::Render(void)
{
	GameObject::Render();
}
