#include "DXUT.h"
#include "GraphicsManager.h"
USING(Engine)

void GraphicsManager::CreateSprite(void)
{
	D3DXCreateSprite(DEVICE, &sprite);
}
