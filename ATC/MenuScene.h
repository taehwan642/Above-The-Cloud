#pragma once
#include "Scene.h"
class MenuScene final:
    public Engine::Scene
{
private:
protected:
public:
    void Start(void) override;
    void Update(const float& dt) override;
    void LateUpdate(void) override;
    void Render(void) override;
    void Exit(void) override;
};

