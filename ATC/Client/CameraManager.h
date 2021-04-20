#pragma once
#include "../Engine/Singleton.h"
class CameraManager :
    public Engine::Singleton<CameraManager>
{
private:
    std::map<CAMERAINDEX, Engine::GameObject*> cameraMap;
    Engine::GameObject* currentCamera = nullptr;

protected:
public:
    explicit CameraManager(void);
    void AddCamera(CAMERAINDEX _key, Engine::GameObject* _camera);
    void SetCamera(CAMERAINDEX _key);

    void UpdateCamera(const FLOAT& dt);
    void LateUpdateCamera(const FLOAT& dt);
    void DeleteCameraDatas(void);
};

