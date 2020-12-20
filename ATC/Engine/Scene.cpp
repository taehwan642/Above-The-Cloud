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
			Safe_Release(layer.second);
		}
	}
	layergroup.clear();
}
