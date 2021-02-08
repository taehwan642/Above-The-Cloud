#pragma once
#include "../Engine/Scene.h"
class MenuScene final :
    public Engine::Scene
{
private:
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

