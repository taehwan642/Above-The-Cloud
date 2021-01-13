#include "DXUT.h"
#include "SceneManager.h"
#include "Layer.h"
#include "ObjectManager.h"
USING(Engine)

void EnemyManager::ClearVector(void)
{
	enemymesh.clear();
	enemyTransform.clear();
}