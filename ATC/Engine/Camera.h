#pragma once
#include "Component.h"
NAMESPACE(Engine)
class Camera final:
    public Component
{
private:
    // Transform?

    D3DXMATRIX viewMatrix;
    D3DXMATRIX projectionMatrix;
protected:
public:
    void SetProjectionMatrix(const D3DXMATRIX& _projectionMatrix);
    void SetProjectionMatrix(const FLOAT& _fov, const FLOAT& _aspect, const FLOAT& _zn, const FLOAT& _zf);
    void SetViewMatrix(const D3DXMATRIX& _viewMatrix);

    explicit Camera(void);

    void Update(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void ResetDevice(void) override;

    void Free(void) override;
};
END