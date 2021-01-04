#pragma once
#include "../Engine/StaticUI.h"
NAMESPACE(Engine)
class PlayerObserver;
class Transform;
END
class AimPoint final : // 이제 Static으로 Sprite로 한번 바꿔서, Screen좌표로 한번 띄워보자!
    public Engine::StaticUI
{
private:
    Engine::Transform* playerTransform;
protected:
public:
    explicit AimPoint(wstring _texturetag);
    virtual ~AimPoint(void);

    void Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};

