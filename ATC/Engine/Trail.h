#pragma once
#include "Component.h"
NAMESPACE(Engine)
class Texture;
class Trail final :
    public Component
{
private:
	struct TrailData
	{
		D3DXVECTOR3 position[2];
		double timecount = 0.0;
		TrailData(const D3DXVECTOR3& upposition, const D3DXVECTOR3& downposition)
			: timecount(0.0)
		{
			position[0] = upposition;
			position[1] = downposition;
		}

	};

private:
	ULONG vtxSize = 0;
	ULONG maxvtxCnt = 0;
	ULONG maxtriCnt = 0;
	ULONG curTriCnt = 0;
	ULONG curVtxCnt = 0;
	double duration = 0.0;
	double alivetime = 0.0;
	size_t lerpcnt = 0;
	float timer = 0.0f;
	float uvRate = 0.0f;
	std::vector<TrailData> trailDatas;

	LPDIRECT3DVERTEXBUFFER9 vb = nullptr;
	LPDIRECT3DINDEXBUFFER9  ib = nullptr;

	Texture* trailTexture = nullptr;

public:
	explicit Trail() {};
	virtual ~Trail() {};

public:
	D3DXMATRIX* worldMatrix;
	HRESULT Initalize(const D3DXMATRIX* _worldMatrix, const ULONG& _bufferSize, const double& _duration, const double& _alivetime, const size_t& _lerpCnt, std::wstring _texturetag);
	void AddNewTrail(const D3DXVECTOR3& _upposition, const D3DXVECTOR3& _downposition, const FLOAT& _dt);
	void SplineTrailPosition(VTXTEX* _vtx, const size_t& _dataindex, ULONG& _index);
	void Update(const FLOAT& dt) override;
	void Render(const FLOAT& dt) override;

	void ClearData(void);

	void Free(void) override;
};
END