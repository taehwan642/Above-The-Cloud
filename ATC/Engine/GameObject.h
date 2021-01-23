#pragma once
#include "Base.h"

NAMESPACE(Engine)
class Layer;
class Component;
class GameObject :
	public Base
{
private:
protected:
	friend class Layer;

	map<wstring, Component*> componentgroup;
	bool isActive = true;
	ColliderData colliderdata;
public:

	explicit GameObject(void) {};
	virtual ~GameObject(void) {};

	void ResetDevice(void);
	void LostDevice(void);

	virtual void CollisionEvent(const wstring& _objectTag, GameObject* _gameObject) {};
	ColliderData* GetColliderData(void) { return &colliderdata; };

	virtual void Update(const FLOAT& dt);
	virtual void LateUpdate(const FLOAT& dt) {};
	virtual void Render(const FLOAT& dt);

	void Free(void) override;
};
END
