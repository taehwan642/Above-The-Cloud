#pragma once
#include "../Engine/GameObject.h"
NAMESPACE(Engine)
class StaticMesh;
class Transform;
END
class test final :
    public Engine::GameObject
{
private:
protected:
public:
    explicit test(void);
    virtual ~test(void);
    
    Engine::StaticMesh* testMesh = nullptr;
    Engine::Transform* transform = nullptr;

    void Update(const float& dt) override;
    void LateUpdate(void) override;
    void Render(void) override;
};

