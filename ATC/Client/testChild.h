#pragma once
#include "../Engine/GameObject.h"
NAMESPACE(Engine)
class GameObject;
class Transform;
class StaticMesh;
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

	Engine::StaticMesh* testsphere = nullptr;
	PlayerObserver* observer;

	Engine::Transform* t;

	void Update(const float& dt) override;
	void LateUpdate(const FLOAT& dt) override;
	void Render(const FLOAT& dt) override;

	void Free(void) override;
};

