#include "DXUT.h"
#include "Scene.h"
#include "SceneManager.h"
USING(Engine)

void SceneManager::AddScene(wstring _name, Scene* _scene)
{
	auto iter = scenegroup.find(_name);
	if (iter == scenegroup.end())
		scenegroup.emplace(_name, _scene);
}

void SceneManager::SetScene(wstring _name)
{
	if (currentScene != nullptr)
		currentScene->Exit();
	currentScene = scenegroup[_name];
	currentScene->Start();
}

void SceneManager::SceneUpdate(const float& dt)
{
	if (currentScene)
	currentScene->Update(dt);
}

void SceneManager::SceneLateUpdate(void)
{
	if (currentScene)
		currentScene->LateUpdate();
}

void SceneManager::SceneRender(void)
{
	if (currentScene)
		currentScene->Render();
}

void SceneManager::LostDevice(void)
{
	if (currentScene)
		currentScene->LostDevice();
}

void SceneManager::ResetDevice(void)
{
	if (currentScene)
		currentScene->ResetDevice();
}
