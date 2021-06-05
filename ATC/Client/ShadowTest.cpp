#include "DXUT.h"
#include "../Engine/Transform.h"
#include "../Engine/Texture.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/RenderManager.h"
#include "ShadowTest.h"

ShadowTest::ShadowTest()
{
	transform = new Engine::Transform();
	componentgroup.emplace(L"Transform", transform);

	texture = dynamic_cast<Engine::Texture*>(Engine::ResourceManager::GetInstance()->LoadResource(L"Start"));
	componentgroup.emplace(L"Texture", texture);

	vtxsize = sizeof(VTXTEX);
	vtxcnt = 4;
	vtxFVF = VTXTEX_FVF;
	tricnt = 2;
	idxsize = sizeof(INDEX16);
	idxfmt = D3DFMT_INDEX16;

	DEVICE->CreateVertexBuffer(vtxsize * vtxcnt, 0, vtxFVF, D3DPOOL::D3DPOOL_MANAGED, &vb, 0);
	DEVICE->CreateIndexBuffer(idxsize * tricnt, 0, idxfmt, D3DPOOL::D3DPOOL_MANAGED, &ib, 0);
	VTXTEX* pVtxTex = NULL;

	vb->Lock(0, 0, reinterpret_cast<void**>(&pVtxTex), 0);

	pVtxTex[0].pos = D3DXVECTOR3(-1.f, 1.f, 0.f);
	pVtxTex[0].uv = D3DXVECTOR2(0.f, 0.f);

	pVtxTex[1].pos = D3DXVECTOR3(1.f, 1.f, 0.f);
	pVtxTex[1].uv = D3DXVECTOR2(1.f, 0.f);

	pVtxTex[2].pos = D3DXVECTOR3(1.f, -1.f, 0.f);
	pVtxTex[2].uv = D3DXVECTOR2(1.f, 1.f);

	pVtxTex[3].pos = D3DXVECTOR3(-1.f, -1.f, 0.f);
	pVtxTex[3].uv = D3DXVECTOR2(0.f, 1.f);

	vb->Unlock();

	INDEX16* pIndex = NULL;

	ib->Lock(0, 0, reinterpret_cast<void**>(&pIndex), 0);

	pIndex[0]._0 = 0;
	pIndex[0]._1 = 1;
	pIndex[0]._2 = 2;

	pIndex[1]._0 = 0;
	pIndex[1]._1 = 2;
	pIndex[1]._2 = 3;

	ib->Unlock();
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
	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	DEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	DEVICE->SetRenderState(D3DRS_ALPHAREF, 0x00000088);

	DEVICE->SetTransform(D3DTS_WORLD, &transform->worldMatrix);
	
	texture->RenderTexture(0);

	DEVICE->SetStreamSource(0, vb, 0, vtxsize);
	DEVICE->SetFVF(vtxFVF);
	DEVICE->SetIndices(ib);
	DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vtxcnt, 0, tricnt);

	GameObject::Render(dt);

	DEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void ShadowTest::Free(void)
{
	vb->Release();
	ib->Release();
	GameObject::Free();
}
