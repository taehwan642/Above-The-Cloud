#pragma once
#include "Singleton.h"
NAMESPACE(Engine)

class Scene;
class Layer;
class GameObject;
class SceneManager final :
    public Singleton<SceneManager>
{
private:
    Scene* currentScene = nullptr;
    std::map<std::wstring, Scene*> scenegroup;
protected:
public:
    void AddScene(std::wstring _name, Scene* _scene);

    void SetScene(std::wstring _name);

    Layer* GetCurrentSceneLayer(LAYERKEY _layerKey);
    
    void AddGameObject(LAYERKEY _layerKey, std::wstring _objectname, GameObject* _gameObject);

    void SceneUpdate(const float& dt);
    void SceneLateUpdate(const FLOAT& dt);
    void SceneRender(const FLOAT& dt);
    void LostDevice(void);
    void ResetDevice(void);

    void ReleaseScenes(void);
};
END