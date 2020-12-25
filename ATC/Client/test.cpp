#include "DXUT.h"
#include "../Engine/Transform.h"
#include "../Engine/StaticMesh.h"
#include "../Engine/DynamicMesh.h"
#include "../Engine/Shader.h"
#include "../Engine/ResourceManager.h"
#include "test.h"

bool testfly = false;
test::test(void)
{
	testshader = dynamic_cast<Engine::Shader*>(Engine::ResourceManager::GetInstance()->LoadResource(L"dyshader"));
	testMesh = dynamic_cast<Engine::StaticMesh*>(Engine::ResourceManager::GetInstance()->LoadResource(L"test"));
	testdynamic = dynamic_cast<Engine::DynamicMesh*>(Engine::ResourceManager::GetInstance()->LoadResource(L"dynamic"));
	componentgroup.emplace(L"shader", testshader);

	transform = new Engine::Transform();
	componentgroup.emplace(L"Transform", transform);
	
	testdynamic->SetParent(&transform->worldMatrix);
	
	transform->scale = D3DXVECTOR3(0.1,0.1,0.1);

	UINT aniset = 0;
	testdynamic->SetAnimationSet(aniset);

	transform->position.z = 50;

	transform->rotation.y = D3DXToRadian(-180);
}

test::~test(void)
{
}

void test::Update(const float& dt)
{
	GameObject::Update(dt);

	D3DXVec3TransformNormal(&directonVector, &lookVector, &transform->worldMatrix);
	D3DXVec3TransformNormal(&wvector, &upVector, &transform->worldMatrix);

	cout << wvector.x << " " << wvector.y << " " << wvector.z << endl;

	if (DXUTWasKeyPressed('U'))
	{
		UINT aniset = testfly ? 0 : 1;
		testfly = !testfly;
		testdynamic->SetAnimationSet(aniset);
	}

	if (DXUTIsKeyDown('W'))
		transform->Rotate(Engine::Transform::RotType::RIGHT, -2.0f * dt);

	if (DXUTIsKeyDown('S'))
		transform->Rotate(Engine::Transform::RotType::RIGHT, 2.f * dt);

	if (DXUTIsKeyDown('A'))
		transform->Rotate(Engine::Transform::RotType::LOOK, -2.f * dt);
	
	if (DXUTIsKeyDown('D'))
		transform->Rotate(Engine::Transform::RotType::LOOK, 2.f * dt);
	
	//transform->position += directonVector * dt * 300;
}

void test::LateUpdate(void)
{
	GameObject::LateUpdate();
}

void test::Render(void)
{
	testdynamic->PlayAnimation(DXUTGetElapsedTime());
	testshader->SetupTable();
	UINT pass = 0;
	LPD3DXEFFECT tempeffect = testshader->GetEffect();
	tempeffect->Begin(&pass, 0);
	tempeffect->BeginPass(0);
	testdynamic->RenderNoSkinnedMesh(tempeffect);
	tempeffect->EndPass();
	tempeffect->End();
	GameObject::Render();
}

void test::Free(void)
{
	GameObject::Free();
}
