#include "DXUT.h"
#include "Transform.h"
#include "Texture.h"
#include "DynamicUI.h"
USING(Engine)
void DynamicUI::CreateBuffer(void)
{
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

DynamicUI::DynamicUI(void)
{
	CreateBuffer();
}

DynamicUI::~DynamicUI(void)
{
}

INT DynamicUI::Update(const FLOAT& dt)
{
	UIBase::Update(dt);
	return OBJALIVE;
}

void DynamicUI::LateUpdate(const FLOAT& dt)
{
	UIBase::LateUpdate(dt);
}

void DynamicUI::Render(const FLOAT& dt)
{
	if (isbillboard)
	{
		D3DXMATRIX matBill;
		D3DXMATRIX matView;
		DEVICE->GetTransform(D3DTS_VIEW, &matView);
		D3DXMatrixIdentity(&matBill);

		memcpy(&matBill, &matView, sizeof(D3DXVECTOR4) * 4);

		D3DXMatrixInverse(&matBill, NULL, &matBill);
		memcpy(&matBill._41, &transform->worldMatrix._41, sizeof(D3DXVECTOR3));

		D3DXVECTOR3 r, u, f;
		memcpy(&r, &matBill._11, sizeof(D3DXVECTOR3));
		memcpy(&u, &matBill._21, sizeof(D3DXVECTOR3));
		memcpy(&f, &matBill._31, sizeof(D3DXVECTOR3));
		r *= D3DXVec3Length(&transform->scale);
		u *= D3DXVec3Length(&transform->scale);
		f *= D3DXVec3Length(&transform->scale);
		memcpy(&matBill._11, &r, sizeof(D3DXVECTOR3));
		memcpy(&matBill._21, &u, sizeof(D3DXVECTOR3));
		memcpy(&matBill._31, &f, sizeof(D3DXVECTOR3));

		DEVICE->SetTransform(D3DTS_WORLD, &matBill);
	}
	else
		DEVICE->SetTransform(D3DTS_WORLD, &transform->worldMatrix);
	UIBase::Render(dt);
}

void DynamicUI::RenderBuffer(void)
{
	DEVICE->SetStreamSource(0, vb, 0, vtxsize);
	DEVICE->SetFVF(vtxFVF);
	DEVICE->SetIndices(ib);
	DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vtxcnt, 0, tricnt);
}

void DynamicUI::Free(void)
{
	vb->Release();
	ib->Release();
	UIBase::Free();
}
