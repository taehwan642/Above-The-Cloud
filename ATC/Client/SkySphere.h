#pragma once
#include "../Engine/GameObject.h"
NAMESPACE(Engine)
class Transform;
class StaticMesh;
class Shader;
END
class SkySphere final :
    public Engine::GameObject
{
private:
protected:
public:
    explicit SkySphere(void);
    virtual ~SkySphere(void);

    Engine::StaticMesh* skysphere = nullptr;
    Engine::Transform* transform = nullptr;
    Engine::Shader* shader = nullptr;

    INT Update(const float& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};
