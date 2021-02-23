#include "DXUT.h"
#include "../Engine/Transform.h"
#include "../Engine/Texture.h"
#include "../Engine/RenderManager.h"
#include "Shadow.h"

Shadow::Shadow(void)
{
}

Shadow::Shadow(Engine::Transform* _objectTransform, const D3DXVECTOR3& _scale)
{
	objectTransform = _objectTransform;
	DynamicUI::SetInformation(L"Shadow");
	SetBillBoardEnable(false);
	transform->scale = _scale;
	D3DXMATRIX mRot;
	D3DXMatrixRotationX(&mRot, D3DXToRadian(90.f));
	D3DXQUATERNION quaternion;
	D3DXQuaternionRotationMatrix(&quaternion, &mRot);
	transform->curQuaternion = quaternion;
	transform->quaternion = quaternion;
}

Shadow::~Shadow(void)
{
}

INT Shadow::Update(const FLOAT& dt)
{
	transform->position = { objectTransform->position.x, -48.f, objectTransform->position.z };
	Engine::RenderManager::GetInstance()->AddRenderObject(ID_NOLIGHT,this);
	DynamicUI::Update(dt);
	return OBJALIVE;
}

void Shadow::LateUpdate(const FLOAT& dt)
{
	DynamicUI::LateUpdate(dt);
}

void Shadow::Render(const FLOAT& dt)
{
	DynamicUI::Render(dt);
}

void Shadow::Free(void)
{
	DynamicUI::Free();
}
