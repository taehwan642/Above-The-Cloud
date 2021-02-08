#include "DXUT.h"
#include "GraphicsManager.h"
USING(Engine)

void GraphicsManager::CreateSprite(void)
{
	D3DXCreateSprite(DEVICE, &sprite);
}

void GraphicsManager::ResetDevice(void)
{
	DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	DEVICE->LightEnable(0, false);	
	if(sprite != nullptr)
		sprite->OnResetDevice();
}

void GraphicsManager::LostDevice(void)
{
	if (sprite != nullptr)
		sprite->OnLostDevice();
}

void GraphicsManager::DeleteSprite(void)
{
	if (sprite != nullptr)
		sprite->Release();
}