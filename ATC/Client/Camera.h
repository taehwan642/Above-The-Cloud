#pragma once
#include "../Engine/GameObject.h"
NAMESPACE(Engine)
class Transform;
END
class Camera final :
    public Engine::Singleton<Camera>, public Engine::GameObject // Singleton으로 받아야할듯
{
private:
protected:
    Engine::Transform* transform = nullptr;
    Engine::Transform* targetTransform = nullptr;
    PlayerObserver* observer;
    float cameraDistance = 10.f;

public:
    bool lookback = false;

    explicit Camera(void);
    virtual ~Camera(void);

    void Update(const float& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;
    void KeyInput(FLOAT _dt);

    void Free(void) override;
};

