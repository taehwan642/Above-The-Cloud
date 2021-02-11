#pragma once
#include "../Engine/GameObject.h"
NAMESPACE(Engine)
class Transform;
END
class PlayerObserver;
class PlaneCamera final :
    public Engine::GameObject
{
private:
protected:
    Engine::Transform* transform = nullptr;
    Engine::Transform* targetTransform = nullptr;
    PlayerObserver* observer;
    float cameraDistance = 10.f;

public:
    bool lookback = false;

    explicit PlaneCamera(void);
    virtual ~PlaneCamera(void);

    void InitCamera(void);

    INT Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};

