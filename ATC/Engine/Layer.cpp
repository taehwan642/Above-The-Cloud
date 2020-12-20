#include "DXUT.h"
#include "GameObject.h"
#include "Layer.h"

USING(Engine)

void Layer::Update(const FLOAT& dt)
{
	for (auto& objectlist : gameobjectgroup)
	{
		for (auto& object : objectlist.second)
		{
			object->Update(dt);
		}
	}
}

void Layer::LateUpdate()
{
	for (auto& objectlist : gameobjectgroup)
	{
		for (auto& object : objectlist.second)
		{
			object->LateUpdate();
		}
	}
}

void Layer::Render()
{
	for (auto& objectlist : gameobjectgroup)
	{
		for (auto& object : objectlist.second)
		{
			object->Render();
		}
	}
}

void Layer::ResetDevice(void)
{
	for (auto& objectlist : gameobjectgroup)
	{
		for (auto& object : objectlist.second)
		{
			object->ResetDevice();
		}
	}
}

void Layer::LostDevice(void)
{
	for (auto& objectlist : gameobjectgroup)
	{
		for (auto& object : objectlist.second)
		{
			object->LostDevice();
		}
	}
}

void Layer::Free(void)
{
	for (auto& objectlist : gameobjectgroup)
	{
		for (auto& object : objectlist.second)
		{
			Safe_Release(object);
		}
		objectlist.second.clear();
	}
	gameobjectgroup.clear();
}
