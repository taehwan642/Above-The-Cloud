#pragma once
#include "Resources.h"

NAMESPACE(Engine)
class StaticMesh :
    public Resources
{
private:
protected:
public:
    explicit StaticMesh(void);
    explicit StaticMesh(const StaticMesh& cp);
    virtual ~StaticMesh(void);

    HRESULT LoadMesh(wstring _filepath, wstring _filename);


    Resources* Clone(void) override;

    void Free(void) override;
};
END