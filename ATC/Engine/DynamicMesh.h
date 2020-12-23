#pragma once
#include "Resources.h"
NAMESPACE(Engine)
class AnimationController;
class MeshHierarchy;
class DynamicMesh final :
    public Resources
{
private:
    D3DXFRAME* rootFrame;
    MeshHierarchy* hierarchy;
    AnimationController* anicontroller;
    list<D3DXMESHCONTAINER_DERIVED*> meshcontainergroup;
protected:
public:
    D3DXMATRIX* parent;
    explicit DynamicMesh(void);
    explicit DynamicMesh(D3DXMATRIX* _parent);
    virtual ~DynamicMesh(void);

    HRESULT LoadMesh(wstring _filepath, wstring _filename);
   
    void RenderMesh(LPD3DXEFFECT& _effect);
    void RenderMesh(void);

    void DrawFrame(LPD3DXFRAME _frame);
    void DrawMeshContainer(LPD3DXMESHCONTAINER _meshcontainer, LPD3DXFRAME _frame);

    void RenderNoSkinnedMesh(LPD3DXEFFECT& _effect);
    void RenderNoSkinnedMesh(void);

    D3DXFRAME_DERIVED* FindBone(const wstring& _bonename);

    void SetAnimationSet(UINT& _index);
    void ResetAnimation(void);
    void PlayAnimation(const FLOAT& _dt, const FLOAT& _movelimit = 0.1f);
    void UpdateFrameMatrices(D3DXFRAME_DERIVED* _frame, const D3DXMATRIX* _parentMatrix, const float& _movelimit = 0.1f);
    void SetUpFrameMatrixPointer(D3DXFRAME_DERIVED* _frame);

    Resources* Clone(void) override;
    void Free(void) override;
};
END
