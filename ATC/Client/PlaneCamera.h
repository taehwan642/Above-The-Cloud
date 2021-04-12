#pragma once
#include "../Engine/GameObject.h"
NAMESPACE(Engine)
class Transform;
class Camera;
END
class PlayerObserver;
class PlaneCamera final :
    public Engine::GameObject
{
private:
    Engine::Transform* transform = nullptr;
    Engine::Transform* targetTransform = nullptr;
    PlayerObserver* observer = nullptr;
    float cameraDistance = 10.f;
    Engine::Camera* camera = nullptr;

protected:
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

