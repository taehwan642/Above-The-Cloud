#pragma once
#include "../Engine/GameObject.h"
NAMESPACE(Engine)
class Transform;
class test;
END
class Camera final :
    public Engine::GameObject
{
private:
    test* player = nullptr;
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

