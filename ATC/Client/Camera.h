#pragma once
#include "../Engine/GameObject.h"
NAMESPACE(Engine)
class Transform;
END
class Camera final :
    public Engine::GameObject
{
private:
protected:
    Engine::Transform* transform = nullptr;
public:
    bool lookback = false; 
    PlayerObserver* observer;
    explicit Camera(void);
    virtual ~Camera(void);

    void Update(const float& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};

