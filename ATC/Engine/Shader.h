#pragma once
#include "Resources.h"

NAMESPACE(Engine)
class Shader :
    public Resources
{
private:
    LPD3DXEFFECT effect = nullptr;
    LPD3DXBUFFER errormsg = nullptr;
protected:
public:
    explicit Shader(void);
    explicit Shader(const Shader& cp);
    virtual ~Shader(void);

    void ResetDevice(void) override;
    void LostDevice(void) override;

    HRESULT CreateShader(wstring _filepath);

    LPD3DXEFFECT GetEffect(void) { return effect; };
    
    HRESULT SetupTable(void);

    Resources* Clone(void) override;

    void Free(void) override;
};
END
