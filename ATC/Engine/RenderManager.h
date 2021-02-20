#pragma once
#include "Singleton.h"
NAMESPACE(Engine)
class GameObject;
class RenderManager :
    public Singleton<RenderManager>
{
private:
    std::list<GameObject*> renderObjects[4];
    void RenderNoLight(void);
    void RenderNormalMesh(void);
    void RenderAlphaTexture(void);
    void RenderEffect(void);

protected:
public:
    void AddRenderObject(RenderID id, GameObject* _object);
    void RenderObject(const FLOAT& dt);
    void ReleaseAllObjects(void);
};
END