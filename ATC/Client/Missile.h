#pragma once
#include "../Engine/GameObject.h"
NAMESPACE(Engine)
class Trail;
class Collider;
class Transform;
class StaticMesh;
END
class Missile :
    public Engine::GameObject
{
private:
    Engine::Transform* transform;
    Engine::StaticMesh* mesh;
    Engine::Collider* collider;
    Engine::Trail* trail;
    LPD3DXMESH test;
protected:
public:
    explicit Missile(void);
    virtual ~Missile(void);

    void Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};