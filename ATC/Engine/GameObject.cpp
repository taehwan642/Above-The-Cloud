#include "DXUT.h"
#include "Layer.h"
#include "Component.h"
#include "CollisionManager.h"
#include "GameObject.h"

USING(Engine)

void GameObject::ResetDevice(void)
{
	for (auto& component : componentgroup)
	{
		component.second->ResetDevice();
	}
}

void GameObject::LostDevice(void)
{
	for (auto& component : componentgroup)
	{
		component.second->LostDevice();
	}
}

void GameObject::Update(const FLOAT& dt)
{
	for (auto& component : componentgroup)
	{
		component.second->Update(dt);
	}
}

void GameObject::Render(const FLOAT& dt)
{
	for (auto& component : componentgroup)
	{
		component.second->Render(dt);
	}
}

void GameObject::Free(void)
{
	for (auto it : componentgroup)
	{
		Safe_Release(it.second);
	}
	componentgroup.clear();
}
