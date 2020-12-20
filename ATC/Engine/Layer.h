#pragma once
#include "Base.h"

NAMESPACE(Engine)
class GameObject;
class Layer : 
	public Base
{
private:
protected:
public:
	map<wstring, list<GameObject*>> gameobjectgroup;

	void Update(const FLOAT& dt);
	void LateUpdate();
	void Render();

	void ResetDevice(void);
	void LostDevice(void);

	void Free(void) override;
};
END
