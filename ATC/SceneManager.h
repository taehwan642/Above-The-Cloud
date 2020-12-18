#pragma once
#include "Singleton.h"
NAMESPACE(Engine)

class Scene;
class SceneManager :
    public Singleton<SceneManager>
{
private:
    Scene* currentScene = nullptr;
    map<wstring, Scene*> scenegroup;
protected:
public:
    void AddScene(wstring _name, Scene* _scene);

    void SetScene(wstring _name);

    void SceneUpdate(const float& dt);
    void SceneLateUpdate(void);
    void SceneRender(void);
    void LostDevice(void);
    void ResetDevice(void);
};
END