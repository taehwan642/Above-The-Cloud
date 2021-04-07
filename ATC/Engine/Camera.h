#pragma once
#include "Component.h"
NAMESPACE(Engine)
class Camera final:
    public Component
{
private:
protected:
public:
    explicit Camera(void);

    void Update(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};
END