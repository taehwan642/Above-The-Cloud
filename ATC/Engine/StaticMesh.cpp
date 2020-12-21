#include "DXUT.h"
#include "StaticMesh.h"

USING(Engine)
StaticMesh::StaticMesh(void)
{

}

StaticMesh::StaticMesh(wstring _filepath, wstring _filename)
{
	LoadMesh(_filepath, _filename);
}

StaticMesh::StaticMesh(const StaticMesh& cp) :
	Resources(cp),
	adjacencyBuffer(cp.adjacencyBuffer),
	subsetBuffer(cp.subsetBuffer),
	mesh(cp.mesh),
	subsetCount(cp.subsetCount),
	oriMesh(cp.oriMesh),
	numVertex(cp.numVertex),
	stride(cp.stride),
	vertexPosition(cp.vertexPosition),
	index(cp.index),
	numFaces(cp.numFaces)
{
	textures = new LPDIRECT3DTEXTURE9[cp.subsetCount];
	for (UINT i = 0; i < cp.subsetCount; ++i)
	{
		textures[i] = nullptr;
		if (cp.textures[i] == nullptr)
			continue;
		textures[i] = cp.textures[i];
		textures[i]->AddRef();
	}
	mesh->AddRef();
	oriMesh->AddRef();
	adjacencyBuffer->AddRef();;
	subsetBuffer->AddRef();
}

StaticMesh::~StaticMesh(void)
{

}

HRESULT StaticMesh::LoadMesh(wstring _filepath, wstring _filename)
{

	HRESULT hr;
	WCHAR finalpath[MAX_PATH];
	
	::lstrcpy(finalpath, _filepath.c_str());
	::lstrcat(finalpath, _filename.c_str());

	hr = D3DXLoadMeshFromX(finalpath, 
						   D3DXMESH_MANAGED, 
						   DEVICE, 
						   &adjacencyBuffer, 
						   &subsetBuffer, 
						   NULL, 
						   &subsetCount, 
						   &oriMesh);

	ULONG FVF = oriMesh->GetFVF();
	
	if (!(FVF & D3DFVF_NORMAL))
	{
		oriMesh->CloneMeshFVF(oriMesh->GetOptions(), FVF | D3DFVF_NORMAL, DEVICE, &mesh);
		D3DXComputeNormals(mesh, static_cast<ULONG*>(adjacencyBuffer->GetBufferPointer()));
	}
	else
	{
		oriMesh->CloneMeshFVF(oriMesh->GetOptions(), FVF, DEVICE, &mesh);
	}

	void* pVertex = nullptr;

	numVertex = mesh->GetNumVertices();
	numFaces = mesh->GetNumFaces();

	vertexPosition = new D3DXVECTOR3[numVertex];

	index = new INDEX16[numFaces];
	INDEX16* pIndex = nullptr;

	mesh->LockIndexBuffer(0, reinterpret_cast<void**>(&pIndex));
	memcpy(index, pIndex, sizeof(INDEX16) * numFaces);
	mesh->UnlockIndexBuffer();

	mesh->LockVertexBuffer(0, &pVertex);
	D3DVERTEXELEMENT9 element[MAX_FVF_DECL_SIZE];
	::ZeroMemory(element, sizeof(D3DVERTEXELEMENT9) * MAX_FVF_DECL_SIZE);
	mesh->GetDeclaration(element);
	UCHAR offSet = 0;
	for (ULONG i = 0; i < MAX_FVF_DECL_SIZE; ++i)
	{
		if (element[i].Usage == D3DDECLUSAGE_POSITION)
		{
			offSet = static_cast<UCHAR>(element[i].Offset);
			break;
		}
	}
	stride = D3DXGetFVFVertexSize(FVF);
	for (ULONG i = 0; i < numVertex; ++i)
		vertexPosition[i] = *(reinterpret_cast<D3DXVECTOR3*>((static_cast<UCHAR*>(pVertex) + (i * stride + offSet))));
	subset = static_cast<D3DXMATERIAL*>(subsetBuffer->GetBufferPointer());
	
	textures = new LPDIRECT3DTEXTURE9[subsetCount];
	for (ULONG i = 0; i < subsetCount; ++i)
	{
		textures[i] = nullptr;
		if (subset[i].pTextureFilename == nullptr)
			continue;
		WCHAR filename[MAX_PATH] = L"";
		::lstrcpy(finalpath, _filepath.c_str());
		MultiByteToWideChar(CP_ACP, 0, subset[i].pTextureFilename, strlen(subset[i].pTextureFilename), filename, MAX_PATH);
		::lstrcat(finalpath, filename);
		hr = D3DXCreateTextureFromFile(DEVICE,
									   finalpath, 
									   &textures[i]);
	}
	mesh->UnlockVertexBuffer();
	return hr;
}

void StaticMesh::Render(void)
{
	
}

void StaticMesh::RenderMesh(void)
{
	for (int i = 0; i < subsetCount; ++i)
	{
		DEVICE->SetTexture(0, textures[i]);
		mesh->DrawSubset(i);
	}
}

Resources* StaticMesh::Clone(void)
{
	return new StaticMesh(*this);
}

void StaticMesh::Free(void)
{
	for (ULONG i = 0; i < subsetCount; ++i)
		Safe_Release(textures[i]);
	Safe_Release(mesh);
	Safe_Release(oriMesh);
	Safe_Release(adjacencyBuffer);
	Safe_Release(subsetBuffer);
	if (!isCloned)
	{
		SAFE_DELETE_ARRAY(index);
		SAFE_DELETE_ARRAY(vertexPosition);
	}
	SAFE_DELETE_ARRAY(textures);
}
