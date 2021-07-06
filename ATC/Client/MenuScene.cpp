#include "DXUT.h"
#include "../Engine/Layer.h"
#include "../Engine/Button.h"
#include "../Engine/SceneManager.h"
#include "MenuCamera.h"
#include "CameraManager.h"
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
	layergroup.emplace(UI, l);

	startButton = new Engine::Button(L"Start", { 0, 0, 5 });
	startButton->SetButtonFunction([]() {Engine::SceneManager::GetInstance()->SetScene(L"°ÔÀÓ"); });
	l->AddGameObject(L"Objects", startButton);

	CameraManager::GetInstance()->AddCamera(CAM_MENU, new MenuCamera());
	CameraManager::GetInstance()->SetCamera(CAM_MENU);

	//MenuCamera* cam = new MenuCamera();
	//l->AddGameObject(L"Objects", cam);
}

void MenuScene::Update(const FLOAT& dt)
{
	if (DXUTIsMouseButtonDown(VK_LBUTTON))
	{
		if (startButton->IsMouseOn())
		{
			startButton->GetButtonFunction()();
		}
	}
		
	Scene::Update(dt);
	CameraManager::GetInstance()->UpdateCamera(dt);
}

void MenuScene::LateUpdate(const FLOAT& dt)
{
	Scene::LateUpdate(dt);
	CameraManager::GetInstance()->LateUpdateCamera(dt);
}

void MenuScene::Exit(void)
{
	CameraManager::GetInstance()->DeleteCameraDatas();
	Scene::Exit();
}

void MenuScene::Free(void)
{
	Scene::Free();
}
