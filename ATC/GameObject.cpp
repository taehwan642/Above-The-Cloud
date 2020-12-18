#include "DXUT.h"
#include "Component.h"
#include "GameObject.h"

USING(Engine)

void GameObject::ResetDevice(void)
{
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

void GameObject::LateUpdate()
{
	for (auto& component : componentgroup)
	{
		component.second->ResetDevice();
	}
}

void GameObject::Render()
{
	for (auto& component : componentgroup)
	{
		component.second->Render();
	}
}
