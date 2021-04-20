#include "DXUT.h"
#include "../Engine/GameObject.h"
#include "CameraManager.h"

CameraManager::CameraManager(void)
{
}

void
CameraManager::AddCamera(CAMERAINDEX _key, Engine::GameObject* _camera)
{
	auto iter = cameraMap.find(_key);
	if (iter == cameraMap.end())
	{
		_camera->SetActive(false);
		cameraMap.emplace(_key, _camera);
	}
}

void 
CameraManager::SetCamera(CAMERAINDEX _key)
{
	if (currentCamera != nullptr)
		currentCamera->SetActive(false);
	currentCamera = cameraMap[_key];
	currentCamera->SetActive(true);
}

void 
CameraManager::UpdateCamera(const FLOAT& dt)
{
	if (currentCamera != nullptr)
		currentCamera->Update(dt);
}

void 
CameraManager::LateUpdateCamera(const FLOAT& dt)
{
	if (currentCamera != nullptr)
		currentCamera->LateUpdate(dt);
}

void 
CameraManager::DeleteCameraDatas(void)
{
	for (auto& it : cameraMap)
	{
		it.second->Release();
	}
	cameraMap.clear();
}
