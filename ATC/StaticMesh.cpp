#include "DXUT.h"
#include "StaticMesh.h"

USING(Engine)
StaticMesh::StaticMesh(void)
{
}

StaticMesh::StaticMesh(const StaticMesh& cp)
{
}

StaticMesh::~StaticMesh(void)
{
}

HRESULT StaticMesh::LoadMesh(wstring _filepath, wstring _filename)
{
	return S_OK;
}

Resources* StaticMesh::Clone(void)
{
	return new StaticMesh(*this);
}
