#pragma once
#include "../Engine/GameObject.h"
NAMESPACE(Engine)
class Transform;
class StaticMesh;
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

    INT Update(const float& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};
