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
    INT Hp = 5;
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
    queue<function<bool(void)>> movementqueue; // queue로, bool lambda를 담아서 움직임 또는 공격이 끝났다면 r true로 pop시킨ㄷㅏㅏㅏ.

    void CollisionEvent(const wstring& _objectTag, GameObject* _gameObject) override;
    
    INT Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};

