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
    int damage = 1;
    float alivetime = 3.f;
    D3DXVECTOR3 direction;
    Engine::Transform* transform = nullptr;
    Engine::StaticMesh* mesh = nullptr;
    Engine::Shader* shader = nullptr;
    Engine::Collider* collider = nullptr;
protected:
public:
    explicit MonsterBullet(void);
    virtual ~MonsterBullet(void);

    int GetDamageValue(void) const;

    void SetInformation(const D3DXVECTOR3& position, const D3DXVECTOR3& _direction, int _damage = 1);

    void CollisionEvent(const std::wstring& _objectTag, GameObject* _gameObject) override;
    
    INT Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};

