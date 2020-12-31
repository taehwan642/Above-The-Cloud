#include "DXUT.h"
#include "Trail.h"
USING(Engine)
HRESULT Trail::Initalize(const D3DXMATRIX* _worldMatrix, const ULONG& _bufferSize, const ULONG& _lerpCnt, const double& _duration, const double& _alivetime, const size_t& _lerpcnt)
{
	maxvtxCnt = _bufferSize;
	if (maxvtxCnt <= 2)
		return E_FAIL;
	maxtriCnt = maxvtxCnt - 2;
	vtxSize = sizeof(VTXTEX);
	duration = _duration;
	alivetime = _alivetime;
	lerpcnt = _lerpcnt;

	if (FAILED(DEVICE->CreateVertexBuffer(maxvtxCnt * vtxSize, 0, VTXTEX_FVF, D3DPOOL_MANAGED, &vb, nullptr)))
		return E_FAIL;

	if (FAILED(DEVICE->CreateIndexBuffer(sizeof(INDEX16) * maxtriCnt, 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &ib, nullptr)))
		return E_FAIL;

	return S_OK;
}

void Trail::AddNewTrail(const D3DXVECTOR3& _upposition, const D3DXVECTOR3& _downposition, const FLOAT& dt)
{
	timer += dt;
	if (duration < static_cast<double>(timer))
	{
		TrailData data(_upposition, _downposition);
		trailDatas.emplace_back(data);
		timer = 0;
	}
}

void Trail::SplineTrailPosition(VTXTEX* _vtx, const size_t& _dataindex, ULONG& _index)
{
	D3DXMATRIX im;
	D3DXMatrixInverse(&im, 0, worldMatrix);

	if (maxvtxCnt <= _index)
		return;

	D3DXVec3TransformCoord(&_vtx[_index].pos, &trailDatas[_dataindex].position[0], &im);
	++_index;

	if (maxvtxCnt <= _index)
		return;

	D3DXVec3TransformCoord(&_vtx[_index].pos, &trailDatas[_dataindex].position[1], &im);
	++_index;

	if (maxvtxCnt <= _index)
		return;

	D3DXVECTOR3 vLerpPos[2];

	ULONG iSize = trailDatas.size();

	for (ULONG j = 1; j < lerpcnt; ++j)
	{
		int iEditIndexV0 = (_dataindex < 1 ? 0 : _dataindex - 1);
		int iEditIndexV2 = (_dataindex + 1 >= iSize ? _dataindex : _dataindex + 1);
		int iEditIndexV3 = (_dataindex + 2 >= iSize ? iEditIndexV2 : _dataindex + 2);

		D3DXVec3CatmullRom(&vLerpPos[0],
			&trailDatas[iEditIndexV0].position[0],
			&trailDatas[_dataindex].position[0],
			&trailDatas[iEditIndexV2].position[0],
			&trailDatas[iEditIndexV3].position[0],
			j / float(lerpcnt));

		D3DXVec3CatmullRom(&vLerpPos[1],
			&trailDatas[iEditIndexV0].position[1],
			&trailDatas[_dataindex].position[1],
			&trailDatas[iEditIndexV2].position[1],
			&trailDatas[iEditIndexV3].position[1],
			j / float(lerpcnt));


		D3DXVec3TransformCoord(&_vtx[_index].pos, &vLerpPos[0], &im);
		++_index;

		if (maxvtxCnt <= _index)
			return;

		D3DXVec3TransformCoord(&_vtx[_index].pos, &vLerpPos[1], &im);
		++_index;

		if (maxvtxCnt <= _index)
			return;
	}
}

void Trail::Update(const FLOAT& dt)
{
	auto iterEnd = trailDatas.end();
	for (auto iter = trailDatas.begin(); iter != trailDatas.end(); )
	{
		iter->timecount += dt;

		if (iter->timecount >= alivetime)
			iter = trailDatas.erase(iter);
		else
			++iter;
	}

	if (trailDatas.size() <= 1)
		return;
	VTXTEX* pVertex = nullptr;
	INDEX16* pIndex = nullptr;

	vb->Lock(0, 0, reinterpret_cast<void**>(&pVertex), 0);
	ib->Lock(0, 0, reinterpret_cast<void**>(&pIndex), 0);

	std::size_t dataCnt = trailDatas.size();
	ULONG index = 0;

	for (std::size_t i = 0; i < dataCnt; ++i)
	{
		SplineTrailPosition(pVertex, i, index);

		if (maxvtxCnt <= index)
			break;
	}

	uvRate = 1.f / float(index - 2);
	for (UINT i = 0; i < index; i += 2)
	{
		pVertex[i].uv = D3DXVECTOR2(0.f, 1.f - (uvRate * i));
		pVertex[i + 1].uv = D3DXVECTOR2(1.f, 1.f - (uvRate * i));
	}

	curVtxCnt = index;
	curTriCnt = curVtxCnt - 2;
	for (ULONG i = 0; i < curTriCnt; i += 2)
	{
		pIndex[i]._0 = i;
		pIndex[i]._1 = i + 1;
		pIndex[i]._2 = i + 3;
		pIndex[i + 1]._0 = i;
		pIndex[i + 1]._1 = i + 3;
		pIndex[i + 1]._2 = i + 2;
	}

	vb->Unlock();
	ib->Unlock();
}

void Trail::Render(const FLOAT& dt)
{
	if (trailDatas.size() <= 1)
		return;

	DEVICE->SetStreamSource(0, vb, 0, vtxSize);
	DEVICE->SetFVF(VTXTEX_FVF);
	DEVICE->SetIndices(ib);
	DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, curVtxCnt, 0, curTriCnt);
}

void Trail::Free(void)
{
	vb->Release();
	ib->Release();
	trailDatas.clear();
	worldMatrix = nullptr;
}
