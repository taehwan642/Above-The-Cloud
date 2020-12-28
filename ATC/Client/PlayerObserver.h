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
protected:
public:
    explicit PlayerObserver(void) {};
    virtual ~PlayerObserver(void) {};

    Engine::Transform* GetTransform(void) { return playerTransform; };
    void UpdateObserver(UINT _flag) override;

    void Free(void) override;
};

