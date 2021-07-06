#include "DXUT.h"
#include "../Engine/Transform.h"
#include "../Engine/Texture.h"
#include "../Engine/RenderManager.h"
#include "../Engine/Shader.h"
#include "../Engine/ResourceManager.h"
#include "Shadow.h"

HRESULT Shadow::Initialize(void)
{
	// Initialize three vertices for rendering a triangle
	CUSTOMVERTEX g_Vertices[] =
	{
		{ -1.0f, 1.0f, 0.0f, D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0xff),0,0 }, // 좌하단
		{  1.0f, 1.0f, 0.0f, D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0xff),1,0 }, // 좌상단
		{  1.0f,-1.0f, 0.0f, D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0xff),1,1 }, // 우하단
		{  -1.0f, -1.0f, 0.0f, D3DCOLOR_RGBA(0xff, 0xff, 0xff, 0xff),0,1 }, // 우상단
	};

	// Create the vertex buffer.
	if (FAILED(DEVICE->CreateVertexBuffer(4 * sizeof(CUSTOMVERTEX),
		0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_MANAGED, &g_pVB, NULL)))
	{
		return E_FAIL;
	}

	if (FAILED(DEVICE->CreateIndexBuffer(2 * sizeof(INDEX16), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED,
		&g_pIB, NULL)))
		return E_FAIL;

	// Fill the vertex buffer.
	VOID* pVertices;
	if (FAILED(g_pVB->Lock(0, sizeof(g_Vertices), (void**)&pVertices, 0)))
		return E_FAIL;
	memcpy(pVertices, g_Vertices, sizeof(g_Vertices));
	g_pVB->Unlock();

	INDEX16* pindex;
	if (FAILED(g_pIB->Lock(0, 0, (void**)&pindex, 0)))
		return E_FAIL;
	pindex[0]._0 = 0;
	pindex[0]._1 = 1;
	pindex[0]._2 = 2;

	pindex[1]._0 = 0;
	pindex[1]._1 = 2;
	pindex[1]._2 = 3;
	g_pIB->Unlock();
}

Shadow::Shadow(void)
{
}

Shadow::Shadow(Engine::Transform* _objectTransform, const D3DXVECTOR3& _scale)
{
	objectTransform = _objectTransform;
	objectTransform->AddReference();
	
	transform = new Engine::Transform();
	componentgroup.emplace(L"Transform", transform);
	transform->localPosition.z = 5;
	texture = dynamic_cast<Engine::Texture*>(Engine::ResourceManager::GetInstance()->LoadResource(L"Shadow"));
	componentgroup.emplace(L"Texture", texture);

	shadowScale = _scale;
	D3DXMATRIX mRot;
	D3DXMatrixRotationX(&mRot, D3DXToRadian(90.f));
	D3DXQUATERNION quaternion;
	D3DXQuaternionRotationMatrix(&quaternion, &mRot);
	transform->curQuaternion = quaternion;
	transform->quaternion = quaternion;
	componentgroup.emplace(L"Transform", transform);

	Initialize();

	DEVICE->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	DEVICE->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	DEVICE->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	DEVICE->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	alpha = 0;
}

Shadow::~Shadow(void)
{
}

void Shadow::ResetSize(void)
{
	transform->scale = { 1,1,1 };
}

INT Shadow::Update(const FLOAT& dt)
{
	transform->localPosition = { objectTransform->localPosition.x, -42.f, objectTransform->localPosition.z };
	transform->scale = (objectTransform->localPosition.y > -41) ?  shadowScale * (objectTransform->localPosition.y - -41.f) : D3DXVECTOR3(0, 0, 0);
	
	// 1. 거리 계산
	D3DXVECTOR3 V = objectTransform->localPosition - transform->localPosition;
	// 피타고라스의 정리에서 c^2 부분.
	FLOAT dist = D3DXVec3LengthSq(&V);
	// 보이기 시작하는 부분.
	if (objectTransform->localPosition.y <= 60)
	{
		// 거리는 가까이 갈수록 줄어들지만, 알파값은 가까이 갈수록 늘어난다.
		// 특정 값 - 거리
		int res = 500 - dist; // 변수값 설정.
		if (res > 255)
			res = 255;
		if (res < 0)
			res = 0;
		alpha = res;
	}
	// 
	
	Engine::RenderManager::GetInstance()->AddRenderObject(ID_NORMALMESH,this);
	GameObject::Update(dt);
	return OBJALIVE;
}

void Shadow::LateUpdate(const FLOAT& dt)
{
	GameObject::LateUpdate(dt);
}

void Shadow::Render(const FLOAT& dt)
{
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE); // 알파블렌딩 사용

	DEVICE->SetTransform(D3DTS_WORLD, &transform->worldMatrix);

	CUSTOMVERTEX* pVertices;
	if (FAILED(g_pVB->Lock(0, 0, (void**)&pVertices, 0)))
		return;
	pVertices[0].color = D3DCOLOR_RGBA(0xff, 0xff, 0xff, alpha);
	pVertices[1].color = D3DCOLOR_RGBA(0xff, 0xff, 0xff, alpha);
	pVertices[2].color = D3DCOLOR_RGBA(0xff, 0xff, 0xff, alpha);
	pVertices[3].color = D3DCOLOR_RGBA(0xff, 0xff, 0xff, alpha);
	g_pVB->Unlock();

	texture->RenderTexture(0);
	DEVICE->SetStreamSource(0, g_pVB, 0, sizeof(CUSTOMVERTEX));
	DEVICE->SetFVF(D3DFVF_CUSTOMVERTEX);
	DEVICE->SetIndices(g_pIB);
	DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	GameObject::Render(dt);
}

void Shadow::Free(void)
{
	if (g_pVB != NULL)
		g_pVB->Release();
	if (g_pIB != NULL)
		g_pIB->Release();
	Safe_Release(objectTransform);
	GameObject::Free();
}
