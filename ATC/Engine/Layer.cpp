#include "DXUT.h"
#include "GameObject.h"
#include "Layer.h"

USING(Engine)

void Layer::AddGameObject(const std::wstring& _objectKey, GameObject* _object)
{
	if (_object == nullptr)
		return;
	
	auto& iter = gameobjectgroup.find(_objectKey);
	if (iter == gameobjectgroup.end())
		gameobjectgroup[_objectKey] = std::list<GameObject*>();

	gameobjectgroup[_objectKey].push_back(_object);
}

void Layer::Update(const FLOAT& dt)
{
	for (auto& objectlist : gameobjectgroup)
	{
		auto& iter = objectlist.second.begin();
		const auto& iter_end = objectlist.second.end();
		for (; iter != iter_end;)
		{
			if ((*iter)->Update(dt) == OBJDEAD)
			{
				Safe_Release(*iter);
				iter = objectlist.second.erase(iter);
			}
			else
				++iter;
		}
	}
}

void Layer::LateUpdate(const FLOAT& dt)
{
	for (auto& objectlist : gameobjectgroup)
	{
		for (auto& object : objectlist.second)
		{
			if (object->GetActive() == true)
				object->LateUpdate(dt);
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
