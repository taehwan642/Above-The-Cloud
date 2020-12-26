#include "DXUT.h"
#include "../Engine/SubjectManager.h"
#include "PlayerObserver.h"
#include "../Engine/Transform.h"
#include "testChild.h"

testChild::testChild(void)
{
	observer = new PlayerObserver();
	Engine::SubjectManager::GetInstance()->Subscribe(observer);
	Engine::SubjectManager::GetInstance()->Notify(static_cast<UINT>(PlayerInfos::PLAYERTRANSFORM));
	t = observer->GetTransform();
}

testChild::~testChild(void)
{
}

void testChild::Update(const float& dt)
{
	cout << t->position.x << endl;
}

void testChild::LateUpdate(const FLOAT& dt)
{
}

void testChild::Render(const FLOAT& dt)
{
}

void testChild::Free(void)
{
}
