#include "DXUT.h"
#include "GameObject.h"
#include "RenderManager.h"
USING(Engine)

void RenderManager::RenderNoLight(void)
{
	// Light false
}

void RenderManager::RenderNormalMesh(void)
{

}

void RenderManager::RenderAlphaTexture(void)
{

}

void RenderManager::RenderEffect(void)
{
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	DEVICE->SetRenderState(D3DRS_ALPHAREF, 0x00000088);


	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void RenderManager::AddRenderObject(RenderID id, GameObject* _object)
{
	renderObjects[id].emplace_back(_object);
	_object->AddReference();
}

void RenderManager::RenderObject(const FLOAT& dt)
{
	for (int i = 0; i < ID_RENDEREND; ++i)
	{
		for (auto& iter : renderObjects[i])
		{
			iter->Render(dt);
		}
	}
}

void RenderManager::ReleaseAllObjects(void)
{
	for (int i = 0; i < ID_RENDEREND; ++i)
	{
		for (auto& iter : renderObjects[i])
		{
			Safe_Release(iter);
		}
		renderObjects[i].clear();
	}
}
