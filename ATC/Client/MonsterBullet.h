#pragma once
#include "../Engine/GameObject.h"
NAMESPACE(Engine)
class Collider;
class Transform;
class StaticMesh;
class Shader;
END
class MonsterBullet final :
    public Engine::GameObject
{
private:
    Engine::Transform* transform = nullptr;
    Engine::StaticMesh* mesh = nullptr;
    Engine::Shader* shader = nullptr;
    Engine::Collider* collider = nullptr;
protected:
public:
    explicit MonsterBullet(void);
    virtual ~MonsterBullet(void);

    void Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};

