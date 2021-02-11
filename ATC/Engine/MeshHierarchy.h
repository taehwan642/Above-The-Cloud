#pragma once
NAMESPACE(Engine)
class MeshHierarchy final :
	public ID3DXAllocateHierarchy
{
private:
    std::wstring filepath = L"";

    void AllocateName(char** destination, const char* name);
protected:
public:
    explicit MeshHierarchy(void);
    explicit MeshHierarchy(std::wstring _path);
    virtual  ~MeshHierarchy(void);

    STDMETHOD(CreateFrame)(THIS_ LPCSTR Name,
        LPD3DXFRAME* ppNewFrame);
	STDMETHOD(CreateMeshContainer)(THIS_
        LPCSTR Name,
        CONST D3DXMESHDATA* pMeshData,
        CONST D3DXMATERIAL* pMaterials,
        CONST D3DXEFFECTINSTANCE* pEffectInstances,
        DWORD NumMaterials,
        CONST DWORD* pAdjacency,
        LPD3DXSKININFO pSkinInfo,
        LPD3DXMESHCONTAINER* ppNewMeshContainer);


    STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree);
    STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree);

    DWORD Release(void);
};
END
