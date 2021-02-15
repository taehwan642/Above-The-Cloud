#pragma once
#include "../Engine/Scene.h"

class GameScene final :
    public Engine::Scene
{
private:
    Stage stage = STAGE1;
    void AddStage1Data(void);
    void AddStage2Data(void);
    void AddStage3Data(void);

protected:
public:
    explicit GameScene(void) {};
    virtual ~GameScene(void) {};

    void Start(void) override;
    void Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Exit(void) override;

    void Free(void) override;
};

