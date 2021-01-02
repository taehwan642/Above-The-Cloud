#pragma once
#include "Singleton.h"
NAMESPACE(Engine)
class GraphicsManager final :
    public Singleton<GraphicsManager>
{
private:
    LPD3DXSPRITE sprite;
protected:
public:
    void CreateSprite(void);
    LPD3DXSPRITE GetSprite(void) { return sprite; }
};
END
