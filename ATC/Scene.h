#pragma once
#include "Base.h"

NAMESPACE(Engine)

class Layer;
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

	virtual void Start(void) PURE;
	virtual void Update(const FLOAT& dt) PURE;
	virtual void LateUpdate(void) PURE;
	virtual void Render(void) PURE;
	virtual void Exit(void) PURE;

	void Free(void) override;
};
END
