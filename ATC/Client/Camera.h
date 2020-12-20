#pragma once
#include "../Engine/GameObject.h"
class Camera :
    public Engine::GameObject
{
private:
protected:
    Engine::Transform* transformcomponent = nullptr;
public:
    void Update(const float& dt) override;
    void LateUpdate(void) override;
    void Render(void) override;

    void Free(void) override;
};

