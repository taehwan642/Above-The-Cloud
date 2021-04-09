#pragma once
#include "../Engine/GameObject.h"

NAMESPACE(Engine)
class Transform;
class Camera;
END

class MenuCamera final :
    public Engine::GameObject
{
private:
    Engine::Camera* camera = nullptr;
    Engine::Transform* transform = nullptr;
protected:
public:
    explicit MenuCamera(void);
    virtual ~MenuCamera(void);

    INT Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};

