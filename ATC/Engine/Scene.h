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
	std::map<LAYERKEY, Layer*> layergroup;
public:
	explicit Scene(void) {};
	virtual ~Scene(void) {};

	void ResetDevice(void);
	void LostDevice(void);

	void AddGameObject(LAYERKEY _layerKey, std::wstring _objecttag, GameObject* _object);
	Layer* GetLayer(LAYERKEY _layerKey);

	virtual void Start(void) PURE;
	virtual void Update(const FLOAT& dt);
	virtual void LateUpdate(const FLOAT& dt);
	virtual void Exit(void);

	void Free(void) override;
};
END
