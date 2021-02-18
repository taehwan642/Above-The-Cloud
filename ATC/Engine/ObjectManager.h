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
    T* GetActiveFalsedObject(LAYERKEY _layerKey, const std::wstring& _objecttag)
    {
        Layer* l = SceneManager::GetInstance()->GetCurrentSceneLayer(_layerKey);
        for (auto& iter : l->gameobjectgroup[_objecttag])
        {
            if (iter->isActive == false)
                return dynamic_cast<T*>(iter);
        }
        return nullptr;
    }

    template<class T>
    T* AddObjectAtLayer(LAYERKEY _layerKey, const std::wstring& _objecttag)
    {
        T* object = new T();
        Layer* l = SceneManager::GetInstance()->GetCurrentSceneLayer(_layerKey);
        l->AddGameObject(_objecttag, object);
        return dynamic_cast<T*>(object);
    }

    template<class T>
    T* CheckActiveFalsedObjectAndSpawn(LAYERKEY _layerKey, const std::wstring& _objecttag)
    {
        T* object = GetActiveFalsedObject<T>(_layerKey, _objecttag);
        if (object == nullptr)
        {
            return AddObjectAtLayer<T>(_layerKey, _objecttag);
        }
        return object;
    }
};
END