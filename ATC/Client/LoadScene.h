#pragma once
#include "../Engine/Scene.h"
class LoadScene :
    public Engine::Scene
{
private:
protected:
public:
    explicit LoadScene(void);
    virtual ~LoadScene(void);

    void Start(void) override;
    void Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;
    void Exit(void) override;

    void Free(void) override;
};

