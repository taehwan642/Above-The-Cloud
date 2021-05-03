#pragma once
#include "../Engine/GameObject.h"
NAMESPACE(Engine)
class Camera;
class Transform;
END
class PlayerObserver;

class CutSceneCamera final :
    public Engine::GameObject
{
private:
    Engine::Camera* camera = nullptr;
    Engine::Transform* transform = nullptr;
    CUTSCENEINDEX index{CUTSCENE_NONE};
    PlayerObserver* observer{ nullptr };
    float delta{ 0.0f };

    void LookAt(const D3DXVECTOR3& _look);
    void LookAtBoss(void);
    void LookAtPlane(void);

protected:
public:
    explicit CutSceneCamera(void);
    virtual ~CutSceneCamera(void);

    void SetCutSceneIndex(CUTSCENEINDEX _index);
    CUTSCENEINDEX GetCutSceneIndex(void) const;

    INT Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};