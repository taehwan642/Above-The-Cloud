#include "DXUT.h"
#include "Layer.h"
#include "Scene.h"
#include "GameObject.h"
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

Layer* SceneManager::GetCurrentSceneLayer(wstring _layertag)
{
	if (currentScene != nullptr)
		return currentScene->GetLayer(_layertag);
	return nullptr;
}

void SceneManager::AddGameObject(wstring _layername, wstring _objectname, GameObject* _gameObject)
{
	if(currentScene != nullptr)
		currentScene->AddGameObject(_layername, _objectname, _gameObject);
}

void SceneManager::SceneUpdate(const float& dt)
{
	if (currentScene)
	currentScene->Update(dt);
}

void SceneManager::SceneLateUpdate(const FLOAT& dt)
{
	if (currentScene)
		currentScene->LateUpdate(dt);
}

void SceneManager::SceneRender(const FLOAT& dt)
{
	if (currentScene)
		currentScene->Render(dt);
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
