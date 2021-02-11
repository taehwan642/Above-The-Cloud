#include "DXUT.h"
#include "../Engine/Layer.h"
#include "../Engine/Button.h"
#include "MenuCamera.h"
#include "MenuScene.h"

MenuScene::MenuScene(void)
{
	
}

MenuScene::~MenuScene(void)
{
}

void MenuScene::Start(void)
{
	Engine::Layer* l = new Engine::Layer();
	layergroup.emplace(L"Layer", l);
	b = new Engine::Button(L"Start", { 0, 0, 5 });
	//b->SetButtonFunction([]() {});
	l->AddGameObject(L"Objects", b);
	MenuCamera* cam = new MenuCamera();
	l->AddGameObject(L"Objects", cam);
}

void MenuScene::Update(const FLOAT& dt)
{
	if (b->IsClicked())
		std::cout << "WOW" << std::endl;
	else
		std::cout << "NO" << std::endl;
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
	Scene::Exit();
}

void MenuScene::Free(void)
{
	Scene::Free();
}
