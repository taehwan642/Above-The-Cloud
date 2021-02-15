#pragma once
#include "../Engine/GameObject.h"
NAMESPACE(Engine)
class Transform;
class DynamicMesh;
class Trail;
class Shader;
class Collider;
END
class PlayerObserver;

class MonsterBase :
    public Engine::GameObject
{
private:
protected:
    UINT currentState = MONSTERIDLE;
    INT Hp = 5;
    INT FullHP = 5;
    FLOAT movementspeed = 1.0f;
    Engine::Transform* transform;
    Engine::Shader* shader;
    Engine::Trail* trail;
    Engine::DynamicMesh* mesh;
    Engine::Collider* collider;
    PlayerObserver* observer;

public:
    explicit MonsterBase(void);
    virtual ~MonsterBase(void);

    void GetHit(const FLOAT& _damageamount);

    virtual void Movement(const FLOAT& dt) {};
    std::queue<std::function<bool(void)>> movementqueue;

    virtual void SetInformation(const D3DXVECTOR3& _position);

    void CollisionEvent(const std::wstring& _objectTag, GameObject* _gameObject) override;
    
    INT Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};

