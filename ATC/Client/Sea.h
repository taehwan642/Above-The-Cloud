#pragma once
#include "../Engine/GameObject.h"
NAMESPACE(Engine)
class Shader;
class StaticMesh;
class Transform;
END
class Sea final :
    public Engine::GameObject
{
private:
    Engine::Shader* shader = nullptr;
    Engine::StaticMesh* mesh = nullptr;
    Engine::Transform* transform;
protected:
public:
    float sceneTime = 0.f;
    explicit Sea(void);
    virtual ~Sea(void);

    INT Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};

