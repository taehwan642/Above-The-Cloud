#pragma once
#include "../Engine/GameObject.h"
NAMESPACE(Engine)
class GameObject;
class Transform;
END

class PlayerObserver;
class testChild final : // For Camera Position
	public Engine::GameObject
{
private:
protected:
public:
	explicit testChild(void);
	virtual ~testChild(void);

	LPD3DXMESH testsphere;
	PlayerObserver* observer;

	Engine::Transform* t;

	void Update(const float& dt) override;
	void LateUpdate(const FLOAT& dt) override;
	void Render(const FLOAT& dt) override;

	void Free(void) override;
};

