#include "DXUT.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Layer.h"
#include "Plane.h"
#include "Cloud.h"
#include "SkySphere.h"
#include "PlaneCamera.h"
#include "../Engine/SubjectManager.h"
#include "../Engine/GraphicsManager.h"
#include "AimPoint.h"
#include "HealthPointGroup.h"
#include "../Engine/ObjectManager.h"
#include "../Engine/CollisionManager.h"
#include "LockPoint.h"
#include "MonsterSpawnManager.h"
#include "GameScene.h"

void GameScene::AddStage1Data(void)
{
	MonsterSpawnManager::GetInstance()->AddSpawnData(STAGE1, MONSTER1, 5);
}

void GameScene::AddStage2Data(void)
{

}

void GameScene::AddStage3Data(void)
{

}

void GameScene::Start(void)
{
	Engine::GraphicsManager::GetInstance()->CreateSprite();
	Engine::Layer* l = new Engine::Layer();
	Engine::Layer* l2 = new Engine::Layer();
	Engine::Layer* effect = new Engine::Layer();
	Engine::Layer* Uii = new Engine::Layer();

	layergroup.emplace(OBJ1, l);
	layergroup.emplace(OBJ2, l2);
	layergroup.emplace(EFFECT, effect);
	layergroup.emplace(UI, Uii);
	SkySphere* s = new SkySphere();

	HealthPointGroup* h = new HealthPointGroup();
	
	Cloud* t1 = new Cloud();

	Engine::ObjectManager::GetInstance()->AddObjectAtLayer<Plane>(OBJ2, L"테스트");
	PlaneCamera* c = new PlaneCamera();
	AimPoint* ui = new AimPoint(L"AimPoint");
	LockPoint* ui2 = new LockPoint();
	Scene::AddGameObject(OBJ1, L"a", s);
	Scene::AddGameObject(OBJ2, L"테스트", c);
	Scene::AddGameObject(UI, L"UI", ui);
	Scene::AddGameObject(UI, L"UI", ui2);
	Scene::AddGameObject(UI, L"UI", h);
	Scene::AddGameObject(OBJ2, L"테스트", t1);
	
	AddStage1Data();
	AddStage2Data();
	AddStage3Data();

	MonsterSpawnManager::GetInstance()->SpawnMonstersByData(stage);
}

void GameScene::Update(const FLOAT& dt)
{
	Engine::CollisionManager::GetInstance()->UpdateData();
	if (DXUTWasKeyPressed('P'))
		Engine::SceneManager::GetInstance()->SetScene(L"메뉴");
	Scene::Update(dt);
}

void GameScene::LateUpdate(const FLOAT& dt)
{
	Engine::CollisionManager::GetInstance()->CheckCollision(PLAYER, MONSTER);
	Engine::CollisionManager::GetInstance()->CheckCollision(MISSILE, MONSTER);
	Engine::CollisionManager::GetInstance()->CheckCollision(PLAYER, MONSTERMISSILE);
	Scene::LateUpdate(dt);
}

void GameScene::Exit(void)
{
	Engine::CollisionManager::GetInstance()->ClearData();
	Engine::SubjectManager::GetInstance()->ClearObservers();
	Engine::GraphicsManager::GetInstance()->DeleteSprite();
	Scene::Exit();
}

void GameScene::Free(void)
{
	Scene::Free();
}
