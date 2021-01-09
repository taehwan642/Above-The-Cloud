#include "DXUT.h"
#include "Collider.h"
#include "CollisionManager.h"
USING(Engine)

void CollisionManager::PushData(Collider* _data)
{
	collisiondatas.push_back(_data);
}

void CollisionManager::CheckSphereCollision(Collider* _col1, Collider* _col2)
{
	FLOAT radius1 = _col1->GetRadius();
	FLOAT radius2 = _col2->GetRadius();

	D3DXVECTOR3 center1 = *_col1->GetCenter();
	D3DXVECTOR3 center2 = *_col2->GetCenter();

	D3DXVECTOR3 direction = (center1 - center2);
	FLOAT length = D3DXVec3Length(&direction);
	D3DXVec3Normalize(&direction, &direction);
	if (length <= (radius1 + radius2))
	{
		if (_col1->GetTag() == _col2->GetTag())
		{
			_col1->ishit = true;
			_col1->collisiontag = _col2->GetTag();
			_col2->ishit = true;
			_col2->collisiontag = _col1->GetTag();
		}
	}
}

void CollisionManager::UpdateData(void)
{
	auto& iter = collisiondatas.begin();
	auto& iter_end = collisiondatas.end();

	for (; iter != iter_end;)
	{
		if ((*iter) == nullptr)
			iter = collisiondatas.erase(iter);
		else
			++iter;
	}
	
	iter = collisiondatas.begin();
	for (; iter != iter_end; ++iter)
	{
		for (auto& iter2 = collisiondatas.begin(); iter2 != iter_end; ++iter2)
		{
			if ((*iter) == (*iter2))
				continue;
			
			CheckSphereCollision(*iter, *iter2);
		}
	}
}