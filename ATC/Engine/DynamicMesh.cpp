#include "DXUT.h"
#include "MeshHierarchy.h"
#include "AnimationController.h"
#include "DynamicMesh.h"
USING(Engine)

DynamicMesh::DynamicMesh(void) :
	rootFrame(nullptr),
	hierarchy(nullptr),
	anicontroller(nullptr)
{
}

DynamicMesh::~DynamicMesh(void)
{
}

HRESULT DynamicMesh::LoadMesh(wstring _filepath, wstring _filename)
{
	TCHAR fullpath[MAX_PATH] = L"";
	lstrcpy(fullpath, _filepath.c_str());
	lstrcat(fullpath, _filename.c_str());
	
	hierarchy = new MeshHierarchy(_filepath);
	if (hierarchy == nullptr)
		return E_FAIL;

	LPD3DXANIMATIONCONTROLLER tempcontroller = nullptr;
	if (FAILED(D3DXLoadMeshHierarchyFromX(fullpath, D3DXMESH_MANAGED, DEVICE, hierarchy, NULL, &rootFrame, &tempcontroller)))
		return E_FAIL;

	anicontroller = new AnimationController(tempcontroller);
	if (anicontroller == nullptr)
		return E_FAIL;

	Safe_Release(anicontroller);

	D3DXMATRIX tempMatrix;
	UpdateFrameMatrices(static_cast<D3DXFRAME_DERIVED*>(rootFrame), D3DXMatrixIdentity(&tempMatrix));
	SetUpFrameMatrixPointer(static_cast<D3DXFRAME_DERIVED*>(rootFrame));
	return S_OK;
}

void DynamicMesh::RenderMesh(LPD3DXEFFECT& _effect)
{
	for (auto& meshcontainer : meshcontainergroup)
	{
		D3DXMESHCONTAINER_DERIVED* tempMeshcontainer = meshcontainer;
		for (ULONG i = 0; i < tempMeshcontainer->numBones; ++i)
		{
			tempMeshcontainer->renderingMatrix[i] = tempMeshcontainer->frameOffsetMatrix[i] * (*tempMeshcontainer->frameCombinedMatrix[i]);
		}
		
		void* srcvtx = nullptr;
		void* destvtx = nullptr;

		tempMeshcontainer->originalMesh->LockVertexBuffer(0, &srcvtx);
		tempMeshcontainer->MeshData.pMesh->LockVertexBuffer(0, &destvtx);

		tempMeshcontainer->pSkinInfo->UpdateSkinnedMesh(tempMeshcontainer->renderingMatrix, NULL, srcvtx, destvtx);
		for (UINT i = 0; i < tempMeshcontainer->NumMaterials; ++i)
		{
			_effect->SetTexture((D3DXHANDLE)"g_DiffuseTexture",tempMeshcontainer->textures[i]);
			_effect->CommitChanges();
			tempMeshcontainer->MeshData.pMesh->DrawSubset(i);
		}
	
		tempMeshcontainer->originalMesh->UnlockVertexBuffer();
		tempMeshcontainer->MeshData.pMesh->UnlockVertexBuffer();
	}
}

void DynamicMesh::RenderMesh(void)
{
	for (auto& meshcontainer : meshcontainergroup)
	{
		D3DXMESHCONTAINER_DERIVED* tempMeshcontainer = meshcontainer;
		for (ULONG i = 0; i < tempMeshcontainer->numBones; ++i)
		{
			tempMeshcontainer->renderingMatrix[i] = tempMeshcontainer->frameOffsetMatrix[i] * (*tempMeshcontainer->frameCombinedMatrix[i]);
		}

		void* srcvtx = nullptr;
		void* destvtx = nullptr;

		tempMeshcontainer->originalMesh->LockVertexBuffer(0, &srcvtx);
		tempMeshcontainer->MeshData.pMesh->LockVertexBuffer(0, &destvtx);

		tempMeshcontainer->pSkinInfo->UpdateSkinnedMesh(tempMeshcontainer->renderingMatrix, NULL, srcvtx, destvtx);
		for (UINT i = 0; i < tempMeshcontainer->NumMaterials; ++i)
		{
			DEVICE->SetTexture(0, tempMeshcontainer->textures[i]);
			tempMeshcontainer->MeshData.pMesh->DrawSubset(i);
		}

		tempMeshcontainer->originalMesh->UnlockVertexBuffer();
		tempMeshcontainer->MeshData.pMesh->UnlockVertexBuffer();
	}
}

D3DXFRAME_DERIVED* DynamicMesh::FindBone(const wstring& _bonename)
{
	if (rootFrame == nullptr)
		return nullptr;
	char bonename[MAX_PATH] = "";
	WideCharToMultiByte(CP_ACP, 0, _bonename.c_str(), _bonename.length(), bonename, MAX_PATH, NULL, NULL);

	return static_cast<D3DXFRAME_DERIVED*>(D3DXFrameFind(rootFrame, bonename));
}

void DynamicMesh::SetAnimationSet(UINT& _index)
{
	anicontroller->SetAnimationSet(_index);
}

void DynamicMesh::ResetAnimation(void)
{
	anicontroller->ResetAnimation();
}

void DynamicMesh::PlayAnimation(const FLOAT& _dt, const FLOAT& _movelimit)
{
	anicontroller->PlayAnimation(_dt);
	D3DXMATRIX tempMatrix;
	UpdateFrameMatrices(static_cast<D3DXFRAME_DERIVED*>(rootFrame), D3DXMatrixIdentity(&tempMatrix));
}

void DynamicMesh::UpdateFrameMatrices(D3DXFRAME_DERIVED* _frame, const D3DXMATRIX* _parentMatrix, const float& _movelimit)
{
	if (_frame == nullptr)
		return;

	if (_parentMatrix == nullptr)
		_frame->combinedTransformMatrix = _frame->TransformationMatrix;
	else
		_frame->combinedTransformMatrix = _frame->TransformationMatrix * (*_parentMatrix);

	if (_frame->pFrameSibling != nullptr)
		UpdateFrameMatrices(static_cast<D3DXFRAME_DERIVED*>(_frame->pFrameSibling), _parentMatrix, _movelimit);

	if (_frame->pFrameFirstChild != nullptr)
		UpdateFrameMatrices(static_cast<D3DXFRAME_DERIVED*>(_frame->pFrameFirstChild), &_frame->combinedTransformMatrix), _movelimit;
}

void DynamicMesh::SetUpFrameMatrixPointer(D3DXFRAME_DERIVED* _frame)
{
	if (_frame->pMeshContainer != nullptr)
	{
		D3DXMESHCONTAINER_DERIVED* tempMeshcontainer = static_cast<D3DXMESHCONTAINER_DERIVED*>(_frame->pMeshContainer);
		for (ULONG i = 0; i < tempMeshcontainer->numBones; ++i)
		{
			const char* name = tempMeshcontainer->pSkinInfo->GetBoneName(i);
			D3DXFRAME_DERIVED* frame = static_cast<D3DXFRAME_DERIVED*>(D3DXFrameFind(rootFrame, name));
			tempMeshcontainer->frameCombinedMatrix[i] = &frame->combinedTransformMatrix;
		}
		meshcontainergroup.push_back(tempMeshcontainer);
	}

	if (_frame->pFrameSibling != nullptr)
		SetUpFrameMatrixPointer(static_cast<D3DXFRAME_DERIVED*>(_frame->pFrameSibling));

	if (_frame->pFrameFirstChild != nullptr)
		SetUpFrameMatrixPointer(static_cast<D3DXFRAME_DERIVED*>(_frame->pFrameFirstChild));
}

void DynamicMesh::Free(void)
{
	Safe_Release(anicontroller);
	hierarchy->DestroyFrame(rootFrame);
	Safe_Release(hierarchy);
	meshcontainergroup.clear();
}
