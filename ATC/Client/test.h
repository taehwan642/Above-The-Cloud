#pragma once
#include "../Engine/GameObject.h"
NAMESPACE(Engine)
class StaticMesh;
class DynamicMesh;
class Transform;
class Shader;
class Trail;
END
class test final :
    public Engine::GameObject
{
private:
protected:
    D3DXVECTOR3 lookVector = { 0,0,-1 };
    D3DXVECTOR3 directonVector = { 0,0,0 };
public:
    explicit test(void);
    virtual ~test(void);

    INT healthpoint = 5;

    D3DXVECTOR3 lefttrailpos[2];
    D3DXVECTOR3 righttrailpos[2];

    Engine::Shader* testshader   = nullptr;
    Engine::DynamicMesh* testdynamic = nullptr;
    Engine::Transform* transform = nullptr;
    Engine::Trail* lefttrail = nullptr;
    Engine::Trail* righttrail = nullptr;

    void Update(const float& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};

