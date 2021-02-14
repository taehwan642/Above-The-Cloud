#include "DXUT.h"
#include "GameObject.h"
#include "RenderManager.h"
USING(Engine)

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
