#include "DXUT.h"
#include "MeshHierarchy.h"
USING(Engine)
void MeshHierarchy::AllocateName(char** destination, const char* name)
{
    if (name != nullptr)
    {
        UINT length = strlen(name);
        *destination = new char[length];
        strcpy_s(*destination, length + 1, name);
    }
}

MeshHierarchy::MeshHierarchy(void)
{
}

MeshHierarchy::MeshHierarchy(wstring _path) :
    filepath(_path)
{
}

MeshHierarchy::~MeshHierarchy(void)
{
}

STDMETHODIMP_(HRESULT __stdcall) MeshHierarchy::CreateFrame(LPCSTR Name, LPD3DXFRAME* ppNewFrame)
{
    cout << "?d" << endl;
    D3DXFRAME_DERIVED* frame = new D3DXFRAME_DERIVED;
    ZeroMemory(frame, sizeof(D3DXFRAME_DERIVED));

    AllocateName(&frame->Name, Name);

    frame->combinedTransformMatrix = *D3DXMatrixIdentity(&frame->TransformationMatrix);
    
    *ppNewFrame = frame;
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) MeshHierarchy::CreateMeshContainer(LPCSTR Name, const D3DXMESHDATA* pMeshData, const D3DXMATERIAL* pMaterials, const D3DXEFFECTINSTANCE* pEffectInstances, DWORD NumMaterials, const DWORD* pAdjacency, LPD3DXSKININFO pSkinInfo, LPD3DXMESHCONTAINER* ppNewMeshContainer)
{
    cout << "?" << endl;
    D3DXMESHCONTAINER_DERIVED* meshcontainer = new D3DXMESHCONTAINER_DERIVED;
    ZeroMemory(meshcontainer, sizeof(D3DXMESHCONTAINER_DERIVED));

    AllocateName(&meshcontainer->Name, Name);
    meshcontainer->MeshData.Type = D3DXMESHTYPE_MESH;

    LPD3DXMESH mesh = pMeshData->pMesh;

    ULONG faceNumbers = mesh->GetNumFaces();
    meshcontainer->pAdjacency = new ULONG[faceNumbers * 3];
    memcpy(meshcontainer->pAdjacency, pAdjacency, sizeof(ULONG) * faceNumbers * 3);

    ULONG FVF = mesh->GetFVF();

    if (!(FVF & D3DFVF_NORMAL))
    {
        mesh->CloneMeshFVF(mesh->GetOptions(), FVF | D3DFVF_NORMAL, DEVICE, &meshcontainer->MeshData.pMesh);
        D3DXComputeNormals(meshcontainer->MeshData.pMesh, meshcontainer->pAdjacency);
    }
    else
        mesh->CloneMeshFVF(mesh->GetOptions(), FVF, DEVICE, &meshcontainer->MeshData.pMesh);

    meshcontainer->NumMaterials = (NumMaterials = 0 ? 1 : NumMaterials);

    meshcontainer->pMaterials = new D3DXMATERIAL[meshcontainer->NumMaterials];
    ZeroMemory(meshcontainer->pMaterials, sizeof(D3DXMATERIAL) * meshcontainer->NumMaterials);

    meshcontainer->textures = new LPDIRECT3DTEXTURE9[meshcontainer->NumMaterials];
    ZeroMemory(meshcontainer->textures, sizeof(LPDIRECT3DTEXTURE9) * meshcontainer->NumMaterials);

    if (NumMaterials != 0)
    {
        memcpy(meshcontainer->pMaterials, pMaterials, sizeof(D3DXMATERIAL) * meshcontainer->NumMaterials);
        for (ULONG i = 0; i < meshcontainer->NumMaterials; ++i)
        {
            TCHAR fullpath[MAX_PATH] = L"";
            TCHAR filename[256] = L"";


            MultiByteToWideChar(CP_ACP, 0, meshcontainer->pMaterials[i].pTextureFilename,
                strlen(meshcontainer->pMaterials[i].pTextureFilename),
                filename,
                256);

            ::lstrcpy(fullpath, filepath.c_str());
            ::lstrcat(fullpath, filename);

            if (FAILED(D3DXCreateTextureFromFile(DEVICE,
                fullpath,
                &meshcontainer->textures[i])))
                return E_FAIL;
        }
    }
    else
    {
        meshcontainer->pMaterials[0].MatD3D.Diffuse = D3DXCOLOR(0, 0, 0, 0);
        meshcontainer->pMaterials[0].MatD3D.Specular = D3DXCOLOR(0, 0, 0, 0);
        meshcontainer->pMaterials[0].MatD3D.Emissive = D3DXCOLOR(0, 0, 0, 0);
        meshcontainer->pMaterials[0].MatD3D.Ambient = D3DXCOLOR(0, 0, 0, 0);
        meshcontainer->pMaterials[0].MatD3D.Power = 0;

        meshcontainer->textures[0] = nullptr;
    }

    meshcontainer->MeshData.pMesh->CloneMeshFVF(meshcontainer->MeshData.pMesh->GetOptions(),
        meshcontainer->MeshData.pMesh->GetFVF(),
        DEVICE,
        &meshcontainer->originalMesh);

    if (pSkinInfo == nullptr)
    {
        *ppNewMeshContainer = meshcontainer;
        return S_OK;
    }

    meshcontainer->pSkinInfo = pSkinInfo;
    meshcontainer->pSkinInfo->AddRef();
    

    meshcontainer->numBones = meshcontainer->pSkinInfo->GetNumBones();
    
    meshcontainer->frameOffsetMatrix = new D3DXMATRIX[meshcontainer->numBones];
    ZeroMemory(meshcontainer->frameOffsetMatrix, sizeof(D3DXMATRIX) * meshcontainer->numBones);

    meshcontainer->frameCombinedMatrix = new D3DXMATRIX * [meshcontainer->numBones];
    ZeroMemory(meshcontainer->frameCombinedMatrix, sizeof(D3DXMATRIX*) * meshcontainer->numBones);

    meshcontainer->renderingMatrix = new D3DXMATRIX[meshcontainer->numBones];
    ZeroMemory(meshcontainer->renderingMatrix, sizeof(D3DXMATRIX) * meshcontainer->numBones);

    for (ULONG i = 0; i < meshcontainer->numBones; ++i)
        meshcontainer->frameOffsetMatrix[i] = *meshcontainer->pSkinInfo->GetBoneOffsetMatrix(i);

    *ppNewMeshContainer = meshcontainer;

    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) MeshHierarchy::DestroyFrame(LPD3DXFRAME pFrameToFree)
{
    SAFE_DELETE_ARRAY(pFrameToFree->Name);
    if (pFrameToFree->pMeshContainer != nullptr)
        DestroyMeshContainer(pFrameToFree->pMeshContainer);
    if (pFrameToFree->pFrameSibling != nullptr)
        DestroyFrame(pFrameToFree->pFrameSibling);
    if (pFrameToFree->pFrameFirstChild != nullptr)
        DestroyFrame(pFrameToFree->pFrameFirstChild);
    SAFE_DELETE(pFrameToFree);
    return S_OK;
}

STDMETHODIMP_(HRESULT __stdcall) MeshHierarchy::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerToFree)
{
    D3DXMESHCONTAINER_DERIVED* meshcontainer = static_cast<D3DXMESHCONTAINER_DERIVED*>(pMeshContainerToFree);
    for (ULONG i = 0; i < meshcontainer->NumMaterials; ++i)
        Safe_Release(meshcontainer->textures[i]);
    SAFE_DELETE_ARRAY(meshcontainer->pAdjacency);
    SAFE_DELETE_ARRAY(meshcontainer->pMaterials);
    SAFE_DELETE_ARRAY(meshcontainer->Name);
    SAFE_DELETE_ARRAY(meshcontainer->textures);
    SAFE_DELETE_ARRAY(meshcontainer->frameOffsetMatrix);
    SAFE_DELETE_ARRAY(meshcontainer->frameCombinedMatrix);
    SAFE_DELETE_ARRAY(meshcontainer->renderingMatrix);
    Safe_Release(meshcontainer->MeshData.pMesh);
    Safe_Release(meshcontainer->pSkinInfo);
    Safe_Release(meshcontainer->originalMesh);
    SAFE_DELETE(meshcontainer);
    return S_OK;
}

DWORD MeshHierarchy::Release(void)
{
    delete this;
    return 0;
}
