#pragma once
#include "../Engine/GameObject.h"
NAMESPACE(Engine)
class GameObject;
class Transform;
class StaticMesh;
class Shader;
END
class Cloud final : // For Camera Position
	public Engine::GameObject
{
private:
protected:
public:
	explicit Cloud(void);
	virtual ~Cloud(void);

	Engine::Shader* shader = nullptr;
	Engine::StaticMesh* mesh = nullptr;
	Engine::Transform* transform;
	Engine::Collider* collider;

	void CollisionEvent(const wstring& _objectTag, GameObject* _gameObject) override;

	INT Update(const float& dt) override;
	void LateUpdate(const FLOAT& dt) override;
	void Render(const FLOAT& dt) override;

	void Free(void) override;
};

