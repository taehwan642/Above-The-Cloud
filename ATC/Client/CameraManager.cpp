#include "DXUT.h"
#include "../Engine/GameObject.h"
#include "CutSceneCamera.h"
#include "CameraManager.h"

void
CameraManager::AddCamera(CAMERAINDEX _key, Engine::GameObject* _camera)
{
	auto& const iter = cameraMap.find(_key);
	if (iter == cameraMap.end())
	{
		_camera->SetActive(false);
		cameraMap.emplace(_key, _camera);
	}
}

void
CameraManager::SetCamera(CAMERAINDEX _key)
{
	currentCamera = cameraMap[_key];
	currentIndex = _key;
}

CUTSCENEINDEX CameraManager::GetCurrentCutScene(void) const
{
	if (currentIndex == CAM_CUTSCENE)
		return dynamic_cast<CutSceneCamera*>(currentCamera)->GetCutSceneIndex();
	return CUTSCENE_NONE;
}

void CameraManager::SetCurrentCutScene(CUTSCENEINDEX _index)
{
	if (currentIndex == CAM_CUTSCENE)
		dynamic_cast<CutSceneCamera*>(currentCamera)->SetCutSceneIndex(_index);
}

Engine::GameObject* CameraManager::GetCurrentCamera(void) const
{
	return currentCamera;
}

CAMERAINDEX CameraManager::GetCurrentIndex(void) const
{
	return currentIndex;
}

float CameraManager::GetDelta(void) const
{
	return dynamic_cast<CutSceneCamera*>(currentCamera)->delta;
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
	currentCamera = nullptr;
	for (auto& it : cameraMap)
	{
		it.second->Release();
	}
	cameraMap.clear();
}
