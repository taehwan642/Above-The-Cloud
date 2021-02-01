#pragma once
#include "../Engine/StaticUI.h"
NAMESPACE(Engine)
class Transform;
END
class PlayerObserver;
class LockPoint final :
    public Engine::StaticUI
{
private:
    PlayerObserver* ob = nullptr;
protected:
public:
    explicit LockPoint(void);
    virtual ~LockPoint(void);

    void Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};

