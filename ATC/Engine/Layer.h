#pragma once
#include "Base.h"

NAMESPACE(Engine)
class GameObject;
class Layer final :
	public Base
{
private:
protected:
public:
	explicit Layer(void) {};
	virtual ~Layer(void) {};

	map<wstring, list<GameObject*>> gameobjectgroup;

	void AddGameObject(wstring _objecttag, GameObject* _object);

	void Update(const FLOAT& dt);
	void LateUpdate();
	void Render();

	void ResetDevice(void);
	void LostDevice(void);

	void Free(void) override;
};
END
