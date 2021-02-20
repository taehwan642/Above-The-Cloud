#pragma once
#include "../Engine/Observer.h"
NAMESPACE(Engine)
class Observer;
class Transform;
class GameObject;
END
class PlayerObserver final :
    public Engine::Observer
{
private:
    Engine::Transform* playerTransform = nullptr;
    INT playerHealthpoint = 0;
    Engine::GameObject* missileLock = nullptr;
    bool playerDead = false;
protected:
public:
    explicit PlayerObserver(void) {};
    virtual ~PlayerObserver(void) {};

    Engine::Transform* GetTransform(void) { return playerTransform; };
    INT GetHealthPoint(void) { return playerHealthpoint; }
    Engine::GameObject* GetMissileLock(void) { return missileLock; }
    bool GetIsPlayerDead(void) const const { return playerDead; };

    void UpdateObserver(UINT _flag) override;

    void Free(void) override;
};

