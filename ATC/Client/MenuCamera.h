#pragma once
#include "../Engine/GameObject.h"
class MenuCamera final :
    public Engine::GameObject
{
private:
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

