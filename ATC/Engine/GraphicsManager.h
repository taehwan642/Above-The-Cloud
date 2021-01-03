#pragma once
#include "Singleton.h"
NAMESPACE(Engine)
class GraphicsManager final :
    public Singleton<GraphicsManager>
{
private:
    LPD3DXSPRITE sprite = nullptr;
protected:
public:
    void CreateSprite(void);
    LPD3DXSPRITE GetSprite(void) { return sprite; }
    void ResetDevice(void);
    void LostDevice(void);
    void DeleteSprite(void);
};
END
