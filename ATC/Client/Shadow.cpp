#include "DXUT.h"
#include "../Engine/Transform.h"
#include "../Engine/Texture.h"
#include "../Engine/RenderManager.h"
#include "../Engine/Shader.h"
#include "../Engine/ResourceManager.h"
#include "Shadow.h"

Shadow::Shadow(void)
{
}

Shadow::Shadow(Engine::Transform* _objectTransform, const D3DXVECTOR3& _scale)
{
	objectTransform = _objectTransform;
	objectTransform->AddReference();
	DynamicUI::SetInformation(L"Shadow");
	SetBillBoardEnable(false);
	shadowScale = _scale;
	D3DXMATRIX mRot;
	D3DXMatrixRotationX(&mRot, D3DXToRadian(90.f));
	D3DXQUATERNION quaternion;
	D3DXQuaternionRotationMatrix(&quaternion, &mRot);
	transform->curQuaternion = quaternion;
	transform->quaternion = quaternion;
	componentgroup.emplace(L"Transform", transform);
	shader = dynamic_cast<Engine::Shader*>(Engine::ResourceManager::GetInstance()->LoadResource(L"ShadowShader"));
	componentgroup.emplace(L"Shader", shader);
}

Shadow::~Shadow(void)
{
}

INT Shadow::Update(const FLOAT& dt)
{
	transform->localPosition = { objectTransform->localPosition.x, -42.f, objectTransform->localPosition.z };
	transform->scale = (objectTransform->localPosition.y > -41) ?  shadowScale * (objectTransform->localPosition.y - -41.f) : D3DXVECTOR3(0, 0, 0);
	Engine::RenderManager::GetInstance()->AddRenderObject(ID_NORMALMESH,this);
	DynamicUI::Update(dt);
	return OBJALIVE;
}

void Shadow::LateUpdate(const FLOAT& dt)
{
	DynamicUI::LateUpdate(dt);
}

void Shadow::Render(const FLOAT& dt)
{
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	DEVICE->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	
	D3DMATERIAL9 mtrl;// = InitMtrl(BLACK, BLACK, BLACK, BLACK, 0.0f);
	mtrl.Diffuse = D3DXCOLOR(D3DCOLOR_XRGB(0, 0, 0));
	mtrl.Ambient = D3DXCOLOR(D3DCOLOR_XRGB(0, 0, 0));
	mtrl.Specular = D3DXCOLOR(D3DCOLOR_XRGB(0, 0, 0));
	mtrl.Emissive = D3DXCOLOR(D3DCOLOR_XRGB(0, 0, 0));
	mtrl.Power = 0.0f;
	mtrl.Diffuse.a = 0.1f; // 50% ������

	DEVICE->SetMaterial(&mtrl);
	DynamicUI::Render(dt);
	texture->RenderTexture(DynamicUI::currentTextureindex);
	DynamicUI::RenderBuffer();
	
	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	/*shader->SetupTable(transform->worldMatrix);
	LPD3DXEFFECT tempEffect = shader->GetEffect();
	UINT pass = 0;
	tempEffect->SetFloat((D3DXHANDLE)"alpha", alpha);
	tempEffect->Begin(&pass, 0);
	tempEffect->BeginPass(0);
	texture->RenderTexture(tempEffect, DynamicUI::currentTextureindex);
	tempEffect->CommitChanges();
	DynamicUI::Render(dt);
	DynamicUI::RenderBuffer();
	tempEffect->EndPass();
	tempEffect->End();*/
}

void Shadow::Free(void)
{
	Safe_Release(objectTransform);
	DynamicUI::Free();
}
