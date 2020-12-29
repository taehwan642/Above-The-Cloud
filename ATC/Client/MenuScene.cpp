#include "DXUT.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Layer.h"
#include "test.h"
#include "testChild.h"
#include "SkySphere.h"
#include "Camera.h"
#include "../Engine/SubjectManager.h"
#include "MenuScene.h"


void MenuScene::Start(void)
{
	if (SUCCEEDED(Engine::ResourceManager::GetInstance()->AddMesh(MeshType::STATIC, L"Resources/Meshes/Static/", L"skysphere.X", L"SkySphere")))
		cout << "히히메시잘불러와져땅" << endl;
	if (SUCCEEDED(Engine::ResourceManager::GetInstance()->AddMesh(MeshType::DYNAMIC, L"Resources/Meshes/Dynamic/", L"testdoubleanimation.x", L"dynamic")))
		cout << "다이나믹메시불러와짐" << endl;
	if (SUCCEEDED(Engine::ResourceManager::GetInstance()->AddShader(L"Resources/Shaders/DynamicMeshShader.fx", L"dyshader")))
		cout << "dyShader Load Complete" << endl;
	if (SUCCEEDED(Engine::ResourceManager::GetInstance()->AddTexture(L"Resources/Textures/AimPoint.png", L"AimPoint")))
		cout << "텍스쳐도 됐다" << endl;


	Engine::Layer* l = new Engine::Layer();
	layergroup.emplace(L"테스트", l);
	test* t = new test();
	Camera* c = new Camera();
	//testChild* t1 = new testChild();
	SkySphere* s = new SkySphere();
	Scene::AddGameObject(L"테스트", L"테스트", t);
	Scene::AddGameObject(L"테스트", L"테스트", c);
	Scene::AddGameObject(L"테스트", L"테스트", s);
	//Scene::AddGameObject(L"테스트", L"테스트", t1);

	
}

void MenuScene::Update(const float& dt)
{
	Scene::Update(dt);
}

void MenuScene::LateUpdate(const FLOAT& dt)
{
	
	Scene::LateUpdate(dt);
}

void MenuScene::Render(const FLOAT& dt)
{
	Scene::Render(dt);
}

void MenuScene::Exit(void)
{
	cout << "엑시트" << endl;
	Engine::SubjectManager::GetInstance()->ClearObservers();
	Scene::Exit();
}

void MenuScene::Free(void)
{
	Scene::Free();
}
