#pragma once
#include "../Engine/GameObject.h"
NAMESPACE(Engine)
class GameObject;
class Transform;
class StaticMesh;
class Shader;
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

	Engine::Shader* testshader = nullptr;
	Engine::StaticMesh* testsphere = nullptr;
	PlayerObserver* observer;

	Engine::Transform* t;
	Engine::Collider* collider;

	void CollisionEvent(const wstring& _objectTag, GameObject* _gameObject) override;

	INT Update(const float& dt) override;
	void LateUpdate(const FLOAT& dt) override;
	void Render(const FLOAT& dt) override;

	void Free(void) override;
};

