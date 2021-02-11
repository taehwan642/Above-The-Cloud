#include "DXUT.h"
#include "Layer.h"
#include "Scene.h"

USING(Engine)

void Scene::AddGameObject(std::wstring _layertag, std::wstring _objecttag, GameObject* _object)
{
	auto& iter = layergroup.find(_layertag);
	if (iter != layergroup.end())
		layergroup[_layertag]->AddGameObject(_objecttag, _object);
	else
	{
		Layer* l = new Layer();
		layergroup.emplace(_layertag, l);
		l->AddGameObject(_objecttag, _object);
		l = nullptr;
	}
}

Layer* Scene::GetLayer(std::wstring _layertag)
{
	auto& iter = layergroup.find(_layertag);
	if (iter != layergroup.end())
		return layergroup[_layertag];
	return nullptr;
}

void Scene::Update(const FLOAT& dt)
{
	for (auto& layer : layergroup)
	{
		layer.second->Update(dt);
	}
}

void Scene::LateUpdate(const FLOAT& dt)
{
	for (auto& layer : layergroup)
	{
		layer.second->LateUpdate(dt);
	}
}

void Scene::Render(const FLOAT& dt)
{
	for (auto& layer : layergroup)
	{
		layer.second->Render(dt);
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
