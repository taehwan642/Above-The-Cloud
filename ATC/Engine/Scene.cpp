#include "DXUT.h"
#include "Layer.h"
#include "Scene.h"

USING(Engine)

void Scene::AddGameObject(wstring _layertag, wstring _objecttag, GameObject* _object)
{
	auto& iter = layergroup.find(_layertag);
	if (iter != layergroup.end())
		layergroup[_layertag]->AddGameObject(_objecttag, _object);
}

void Scene::Update(const FLOAT& dt)
{
	for (auto& layer : layergroup)
	{
		layer.second->Update(dt);
	}
}

void Scene::LateUpdate(void)
{
	for (auto& layer : layergroup)
	{
		layer.second->LateUpdate();
	}
}

void Scene::Render(void)
{
	for (auto& layer : layergroup)
	{
		layer.second->Render();
	}
}

void Scene::Exit(void)
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

void Scene::ResetDevice(void)
{
	for (auto& layer : layergroup)
	{
		layer.second->ResetDevice();
	}
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
