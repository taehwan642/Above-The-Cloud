#pragma once
#include "../Engine/GameObject.h"
NAMESPACE(Engine)
class DynamicMesh;
class Transform;
class Shader;
class Trail;
class TextureEffect;
class Collider;
END
class Plane final :
    public Engine::GameObject
{
private:
    FLOAT invincibletime = 1.f;
    Engine::GameObject* dstObject = nullptr;
    FLOAT shootDelay = 0.3f;

protected:
    D3DXVECTOR3 lookVector = { 0,0,-1 };
    D3DXVECTOR3 directionVector = { 0,0,0 };
    D3DXVECTOR3 lefttrailpos[2];
    D3DXVECTOR3 righttrailpos[2];
    D3DXVECTOR3 effectpos[4];

public:
    explicit Plane(void);
    virtual ~Plane(void);

    INT healthpoint = 5;

    Engine::Shader* testshader   = nullptr;
    Engine::DynamicMesh* testdynamic = nullptr;
    Engine::Transform* transform = nullptr;
    Engine::Trail* lefttrail = nullptr;
    Engine::Trail* righttrail = nullptr;
    Engine::Collider* collider = nullptr;

    void CollisionEvent(const std::wstring& _objectTag, GameObject* _gameObject) override;

    INT Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};

