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
	void ResetDevice(void);
	void LostDevice(void);

	void Update(const FLOAT& dt);
	void LateUpdate();
	void Render();

};
END
