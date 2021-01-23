#pragma once
#include "Singleton.h"
NAMESPACE(Engine)
class GameObject;
class CollisionManager :
    public Singleton<CollisionManager>
{
private:
    list<GameObject*> colliderdatas[OBJEND];
    
    bool CheckSphereCollision(const D3DXVECTOR3& srcpos,
                              const FLOAT& srcradius,
                              const D3DXVECTOR3& dstpos,
                              const FLOAT& dstradius);
protected:
public:
    void PushData(ObjectTag _tag , GameObject* _data);

    void CheckCollision(ObjectTag _src, ObjectTag _dst);

    /*bool ObjectRaySphereIntersection(D3DXVECTOR3 _raypos,
                                     D3DXVECTOR3 _raydir,
                                     D3DXVECTOR3 _spherepos,
                                     FLOAT _radius);*/

    void UpdateData(void);

    void ClearData(void);
};
END