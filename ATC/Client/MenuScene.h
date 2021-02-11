#pragma once
#include "../Engine/Scene.h"
NAMESPACE(Engine)
class Button;
END
class MenuScene final :
    public Engine::Scene
{
private:
    Engine::Button* startButton;
protected:
public:
    explicit MenuScene(void);
    virtual ~MenuScene(void);

    void Start(void) override;
    void Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;
    void Exit(void) override;

    void Free(void) override;
};

