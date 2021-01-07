#pragma once
#include "Singleton.h"
NAMESPACE(Engine)
class EnemyManager final :
    public Singleton<EnemyManager>
{
public:
    vector<LPD3DXMESH> enemymesh;
    vector<D3DXMATRIX*> enemyTransform;

    void ClearVector(void);
};
END
