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
    map<wstring, Scene*> scenegroup;
protected:
public:
    void AddScene(wstring _name, Scene* _scene);

    void SetScene(wstring _name);

    Layer* GetCurrentSceneLayer(wstring _layertag);
    
    void AddGameObject(wstring _layername, wstring _objectname, GameObject* _gameObject);

    void SceneUpdate(const float& dt);
    void SceneLateUpdate(const FLOAT& dt);
    void SceneRender(const FLOAT& dt);
    void LostDevice(void);
    void ResetDevice(void);
};
END