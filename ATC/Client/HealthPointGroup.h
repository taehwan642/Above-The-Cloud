#pragma once
#include "../Engine/GameObject.h"
class PlayerObserver;
class HealthPoint;

class HealthPointGroup final :
    public Engine::GameObject
{
private:
    PlayerObserver* observer = nullptr;
    HealthPoint* hp[5];
protected:
public:
    explicit HealthPointGroup(void);
    virtual ~HealthPointGroup(void);

    void Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};

