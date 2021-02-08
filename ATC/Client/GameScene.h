#pragma once
#include "../Engine/Scene.h"

class GameScene final :
    public Engine::Scene
{
private:
protected:
public:
    explicit GameScene(void) {};
    virtual ~GameScene(void) {};

    void Start(void) override;
    void Update(const float& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;
    void Exit(void) override;

    void Free(void) override;
};

