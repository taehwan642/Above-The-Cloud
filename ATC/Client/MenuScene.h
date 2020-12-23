#pragma once
#include "../Engine/Scene.h"

class MenuScene final :
    public Engine::Scene
{
private:
protected:
    float x = 0;
    float z = -5;
public:
    void Start(void) override;
    void Update(const float& dt) override;
    void LateUpdate(void) override;
    void Render(void) override;
    void Exit(void) override;

    void Free(void) override;
};

