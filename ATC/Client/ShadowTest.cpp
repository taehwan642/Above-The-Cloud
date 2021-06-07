#include "DXUT.h"
#include "../Engine/Transform.h"
#include "../Engine/Texture.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/RenderManager.h"
#include "ShadowTest.h"

HRESULT ShadowTest::Initialize(void)
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

ShadowTest::ShadowTest()
{
	transform = new Engine::Transform();
	componentgroup.emplace(L"Transform", transform);
	transform->localPosition.z = 5;
	texture = dynamic_cast<Engine::Texture*>(Engine::ResourceManager::GetInstance()->LoadResource(L"Shadow"));
	componentgroup.emplace(L"Texture", texture);
	Initialize();

	DEVICE->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	DEVICE->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	DEVICE->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	DEVICE->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

INT ShadowTest::Update(const FLOAT& dt)
{
	Engine::RenderManager::GetInstance()->AddRenderObject(RenderID::ID_NORMALMESH, this);
	GameObject::Update(dt);
	return OBJALIVE;
}

void ShadowTest::LateUpdate(const FLOAT& dt)
{
	GameObject::LateUpdate(dt);
}

void ShadowTest::Render(const FLOAT& dt)
{
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE); // 알파블렌딩 사용

	DEVICE->SetTransform(D3DTS_WORLD, &transform->worldMatrix);

	static int alpha = 0;
	static float delta = 0;
	delta += dt;
	alpha =  (255.f - 255 * cos(delta * 10)) > 255 ? 255 : (255.f - 255 * cos(delta * 10));
	
	
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

void ShadowTest::Free(void)
{
	if (g_pVB != NULL)
		g_pVB->Release();
	if (g_pIB != NULL)
		g_pIB->Release();
	GameObject::Free();
}
