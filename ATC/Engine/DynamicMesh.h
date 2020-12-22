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
    explicit DynamicMesh(void);
    virtual ~DynamicMesh(void);

    HRESULT LoadMesh(wstring _filepath, wstring _filename);
   
    void RenderMesh(LPD3DXEFFECT& _effect);
    void RenderMesh(void);

    D3DXFRAME_DERIVED* FindBone(const wstring& _bonename);

    void SetAnimationSet(UINT& _index);
    void ResetAnimation(void);
    void PlayAnimation(const FLOAT& _dt, const FLOAT& _movelimit = 0.1f);
    void UpdateFrameMatrices(D3DXFRAME_DERIVED* _frame, const D3DXMATRIX* _parentMatrix, const float& _movelimit = 0.1f);
    void SetUpFrameMatrixPointer(D3DXFRAME_DERIVED* _frame);

    void Free(void) override;
};
END
