#pragma once
#include "SceneManager.h"
#include "Layer.h"
#include "Singleton.h"
NAMESPACE(Engine)

class Layer;
class SceneManager;
class ObjectManager final :
    public Singleton<ObjectManager>
{
public:
    template<class T>
    T* GetActiveFalsedObject(const wstring& _layertag, const wstring& _objecttag)
    {
        Layer* l = SceneManager::GetInstance()->GetCurrentSceneLayer(_layertag);
        for (auto& iter : l->gameobjectgroup[_objecttag])
        {
            if (iter->isActive == false)
                return dynamic_cast<T*>(iter);
        }
        return nullptr;
    }


    template<class T>
    T* AddObjectAtLayer(const wstring& _layertag, const wstring& _objecttag)
    {
        T* object = new T();
        Layer* l = SceneManager::GetInstance()->GetCurrentSceneLayer(_layertag);
        l->AddGameObject(_objecttag, object);
        return object;
    }
};
END