#pragma once
#include "Base.h"

NAMESPACE(Engine)
class Component;
class GameObject :
	public Base
{
private:
protected:
	map<wstring, Component*> componentgroup;
public:
	explicit GameObject(void) {};
	virtual ~GameObject(void) {};

	void ResetDevice(void);
	void LostDevice(void);

	virtual void Update(const FLOAT& dt);
	virtual void LateUpdate(const FLOAT& dt) {};
	virtual void Render(const FLOAT& dt);

	void Free(void) override;
};
END
