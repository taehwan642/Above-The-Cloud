#pragma once
#include "SceneManager.h"
#include "Layer.h"
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
class Layer;
class SceneManager;
class ObjectManager final :
    public Singleton<ObjectManager>
{
public:
    template<class T>
    void AddObjectAtLayer(const wstring& _layertag, const wstring& _objecttag)
    {
        T* object = new T();
        Layer* l = SceneManager::GetInstance()->GetCurrentSceneLayer(_layertag);
        l->AddGameObject(_objecttag, object);
    }
};

END

