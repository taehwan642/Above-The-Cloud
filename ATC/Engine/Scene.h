#pragma once
#include "Base.h"

NAMESPACE(Engine)
class Layer;
class GameObject;

class Scene :
	public Base
{
private:
protected:
	map<wstring, Layer*> layergroup;
public:
	explicit Scene(void) {};
	virtual ~Scene(void) {};

	void ResetDevice(void);
	void LostDevice(void);

	void AddGameObject(wstring _layertag, wstring _objecttag, GameObject* _object);

	virtual void Start(void) PURE;
	virtual void Update(const FLOAT& dt);
	virtual void LateUpdate(void);
	virtual void Render(void);
	virtual void Exit(void);

	void Free(void) override;
};
END
