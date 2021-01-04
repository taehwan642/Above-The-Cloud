#pragma once
#include "../Engine/Observer.h"
NAMESPACE(Engine)
class Observer;
class Transform;
END
class PlayerObserver :
    public Engine::Observer
{
private:
    Engine::Transform* playerTransform = nullptr;
    INT playerHealthpoint = 0;
protected:
public:
    explicit PlayerObserver(void) {};
    virtual ~PlayerObserver(void) {};

    Engine::Transform* GetTransform(void) { return playerTransform; };
    INT GetHealthPoint(void) { return playerHealthpoint; }
    void UpdateObserver(UINT _flag) override;

    void Free(void) override;
};

