#include "DXUT.h"
#include "../Engine/Transform.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/StaticMesh.h"
#include "../Engine/CollisionManager.h"
#include "../Engine/Collider.h"
#include "../Engine/Trail.h"
#include "../Engine/SubjectManager.h"
#include "PlayerObserver.h"
#include "Missile.h"

Missile::Missile(void)
{
	transform = new Engine::Transform();
	componentgroup.emplace(L"transform", transform);
	//mesh = dynamic_cast<Engine::StaticMesh*>(Engine::ResourceManager::GetInstance()->LoadResource(L"Missile"));
	collider = new Engine::Collider(1, &transform->position, ObjectTag::PLAYER);
	Engine::CollisionManager::GetInstance()->PushData(collider);
	componentgroup.emplace(L"collider", collider);
	D3DXCreateSphere(DEVICE, 5, 20, 20, &test, nullptr);

	ob = new PlayerObserver();
	Engine::SubjectManager::GetInstance()->Subscribe(ob);
	Engine::SubjectManager::GetInstance()->Notify(static_cast<UINT>(PlayerInfos::PLAYERTRANSFORM));

	transform->position = ob->GetTransform()->position;
}

Missile::~Missile(void)
{

}

void Missile::Update(const FLOAT& dt)
{
	
	GameObject::Update(dt);
}

void Missile::LateUpdate(const FLOAT& dt)
{
	// ob���� �޾ƿ� �� �� ������ �����͸� �޾ƿ�
	// �� ������ ��ġ�� pos�� �޾Ƽ�
	// x = z,y
	// y = x,z
	// z = y,x
	// rotate look z, up y, right x
	// RAY & SPHERE
	// �ٸ� ��� ������ ��� �ҷ�����?
	// �׳� �ϳ��� �÷��̾��� forward�� �޾Ƽ� �ϴ°� ���ڴ�.
	// �׷� ��� ������ �÷��̾��� obesrver�� ������ �ǰ�,
	// ���� �� Observer ���� UI������ �־��� �� �ְ� ����� �����ڳ�
	// �÷��̾�� �ٸ� ��� ����� �����ؼ�, �÷��̾��� forward�� ���� ����� ������ lock�� �Ǵ�.
	// �׷�����, �ϴ� move�� lock��Ű�� �ּ����� ���� ������ �˾Ƴ�����. (ȭ�� �ۿ��ִ°͵��� lock������ �ȵǴϱ�)
	GameObject::LateUpdate(dt);
}

void Missile::Render(const FLOAT& dt)
{
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	DEVICE->SetTransform(D3DTS_WORLD, &transform->worldMatrix);
	test->DrawSubset(0);
	collider->RenderCollider();
	GameObject::Render(dt);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void Missile::Free(void)
{
	GameObject::Free();
}