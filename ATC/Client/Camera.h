#pragma once
#include "../Engine/GameObject.h"
NAMESPACE(Engine)
class Transform;
END
class Camera :
    public Engine::GameObject
{
private:
protected:
    Engine::Transform* transformcomponent = nullptr;
public:
    explicit Camera(void);
    virtual ~Camera(void);

    void Update(const float& dt) override;
    void LateUpdate(void) override;
    void Render(void) override;

    void Free(void) override;
};

