#include "DXUT.h"
#include "../Engine/Layer.h"
#include "../Client/test.h"
#include "../Client/Camera.h"
#include "MenuScene.h"


void MenuScene::Start(void)
{
	cout << "아 씨~발" << endl;
	Engine::Layer* l = new Engine::Layer();
	layergroup.emplace(L"테스트", l);
	test* t = new test();
	Camera* c = new Camera();
	Scene::AddGameObject(L"테스트", L"테스트", t);
	Scene::AddGameObject(L"테스트", L"테스트", c);
	
}

void MenuScene::Update(const float& dt)
{
	Scene::Update(dt);
}

void MenuScene::LateUpdate(void)
{
	Scene::LateUpdate();
}

void MenuScene::Render(void)
{
	Scene::Render();
}

void MenuScene::Exit(void)
{
	cout << "엑시트" << endl;
	Scene::Exit();
}

void MenuScene::Free(void)
{
	Scene::Free();
}
