#pragma once
#include "../Engine/GameObject.h"
NAMESPACE(Engine)
class Trail;
class Collider;
class Transform;
class StaticMesh;
END
class PlayerObserver;
class Missile :
    public Engine::GameObject
{
private:
    float homingtime = 1.5f;

    Engine::Shader* shader = nullptr; 
    Engine::StaticMesh* mesh;
    Engine::Collider* collider;
    Engine::Trail* trail;
    Engine::Transform* transform;

    PlayerObserver* ob = nullptr;
protected:
public:
    explicit Missile(void);
    virtual ~Missile(void);

    void Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};