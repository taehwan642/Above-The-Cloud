#include "DXUT.h"
#include "GameObject.h"
#include "CollisionManager.h"
USING(Engine)

void CollisionManager::PushData(ObjectTag _tag, GameObject* _data)
{
	colliderdatas[_tag].push_back(_data);
}

bool CollisionManager::CheckSphereCollision(const D3DXVECTOR3& srcpos, const FLOAT& srcradius, const D3DXVECTOR3& dstpos, const FLOAT& dstradius)
{
	D3DXVECTOR3 dir = (srcpos - dstpos);
	FLOAT length = D3DXVec3Length(&dir);
	D3DXVec3Normalize(&dir, &dir);

	return length <= (srcradius + dstradius);
}

void CollisionManager::CheckCollision(ObjectTag _src, ObjectTag _dst)
{
	for (auto& srcobj : colliderdatas[_src])
	{
		for (auto& dstobj : colliderdatas[_dst])
		{
			if (srcobj == dstobj)
				continue;

			ColliderData* srcdata = srcobj->GetColliderData();
			ColliderData* dstdata = dstobj->GetColliderData();

			if (CheckSphereCollision(*srcdata->center, srcdata->radius, *dstdata->center, dstdata->radius))
			{
				srcobj->CollisionEvent(dstdata->tag, dstobj);
				dstobj->CollisionEvent(srcdata->tag, dstobj);
				srcdata->ishit = true;
				dstdata->ishit = true;
			}
		}
	}
}

void CollisionManager::UpdateData(void)
{
	for (int i = 0; i < OBJEND; ++i)
	{
		auto& iter = colliderdatas[i].begin();
		auto& iter_end = colliderdatas[i].end();

		for (; iter != iter_end;)
		{
			if ((*iter) == nullptr)
				iter = colliderdatas[i].erase(iter);
			else
				++iter;
		}
	}
}

void CollisionManager::ClearData(void)
{
	for (int i = 0; i < OBJEND; ++i)
		colliderdatas[i].clear();
}
