#include "DXUT.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Layer.h"
#include "test.h"
#include "testChild.h"
#include "SkySphere.h"
#include "Camera.h"
#include "../Engine/SubjectManager.h"
#include "../Engine/GraphicsManager.h"
#include "AimPoint.h"
#include "HealthPointGroup.h"
#include "SphereMonster.h"
#include "../Engine/EnemyManager.h"
#include "MenuScene.h"


void MenuScene::Start(void)
{
	if (SUCCEEDED(Engine::ResourceManager::GetInstance()->AddMesh(MeshType::STATIC, L"Resources/Meshes/Static/", L"skysphere.X", L"SkySphere")))
		cout << "히히메시잘불러와져땅" << endl;
	if (SUCCEEDED(Engine::ResourceManager::GetInstance()->AddMesh(MeshType::DYNAMIC, L"Resources/Meshes/Dynamic/", L"Plane.X", L"dynamic")))
		cout << "다이나믹메시불러와짐" << endl;
	if (SUCCEEDED(Engine::ResourceManager::GetInstance()->AddShader(L"Resources/Shaders/DynamicMeshShader.fx", L"dyshader")))
		cout << "dyShader Load Complete" << endl;
	if (SUCCEEDED(Engine::ResourceManager::GetInstance()->AddTexture(L"Resources/Textures/AimPoint.png", L"AimPoint")))
		cout << "텍스쳐도 됐다" << endl; 
	if (SUCCEEDED(Engine::ResourceManager::GetInstance()->AddTexture(L"Resources/Textures/heart.png", L"Heart")))
		cout << "2텍스쳐도 됐다" << endl;
	if (SUCCEEDED(Engine::ResourceManager::GetInstance()->AddTexture(L"Resources/Textures/trail.dds", L"TrailTexture")))
		cout << "트레일텍스쳐 됐다" << endl;

	if (SUCCEEDED(Engine::ResourceManager::GetInstance()->AddMesh(MeshType::DYNAMIC, L"Resources/Meshes/Dynamic/", L"m1test.X", L"Monster1")))
		cout << "다이나믹메시불러와짐" << endl;

	if (SUCCEEDED(Engine::ResourceManager::GetInstance()->AddMesh(MeshType::STATIC, L"Resources/Meshes/Static/", L"cloud.X", L"Cloud")))
		cout << "구름나와랑" << endl;
	
	if (SUCCEEDED(Engine::ResourceManager::GetInstance()->AddTexture(L"Resources/Textures/muzzleflash.png", L"muzzleFlash", 1)))
		cout << "머즐플래시 ON" << endl;
	
	
	Engine::GraphicsManager::GetInstance()->CreateSprite();
	Engine::Layer* l = new Engine::Layer();
	Engine::Layer* effect = new Engine::Layer();
	layergroup.emplace(L"테스트", l);
	layergroup.emplace(L"Effect", effect);
	test* t = new test();
	Camera* c = new Camera();
	SkySphere* s = new SkySphere();

	AimPoint* ui = new AimPoint(L"AimPoint");
	HealthPointGroup* h = new HealthPointGroup();
	
	testChild* t1 = new testChild();

	//SphereMonster* sp = new SphereMonster();

	Scene::AddGameObject(L"테스트", L"테스트", t);
	Scene::AddGameObject(L"테스트", L"테스트", c);
	Scene::AddGameObject(L"테스트", L"UI", ui);
	Scene::AddGameObject(L"테스트", L"UI", h);
	Scene::AddGameObject(L"테스트", L"테스트", s);
	Scene::AddGameObject(L"테스트", L"테스트", t1);
	//Scene::AddGameObject(L"테스트", L"테스트", sp);
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
	Engine::GraphicsManager::GetInstance()->DeleteSprite();
	Engine::EnemyManager::GetInstance()->ClearVector();
	Scene::Exit();
}

void MenuScene::Free(void)
{
	Scene::Free();
}
