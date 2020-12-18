#include "DXUT.h"
#include "Layer.h"
#include "Scene.h"

USING(Engine)

void Scene::ResetDevice(void)
{
}

void Scene::LostDevice(void)
{
	for (auto& layer : layergroup)
	{
		layer.second->LostDevice();
	}
}

void Scene::Free(void)
{
	for (auto& layer : layergroup)
	{
		if (layer.second != nullptr)
		{
			ULONG refCount = layer.second->Release();
			if (refCount == 0)
				layer.second = nullptr;
		}
	}
	layergroup.clear();
}
