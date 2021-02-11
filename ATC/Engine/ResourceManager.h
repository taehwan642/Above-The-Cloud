#pragma once
#include "Singleton.h"

NAMESPACE(Engine)
class Resources;
class ResourceManager final :
    public Singleton<ResourceManager>
{
private:
    std::map<std::wstring, Resources*> resourcegroup;
protected:

public:
    HRESULT AddTexture(std::wstring _filepath, std::wstring _tag, const UINT& _texturecount = 1);
    HRESULT AddMesh(MeshType _meshtype, std::wstring _filepath, std::wstring _filename, std::wstring _tag);
    HRESULT AddShader(std::wstring _filepath, std::wstring _tag);

    Resources* LoadResource(std::wstring _tag);

    void ReleaseResources(void);
};
END
