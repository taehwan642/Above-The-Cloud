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
#include "Sea.h"
#include "RadarPlane.h"
#include "CameraManager.h"
#include "CutSceneCamera.h"
#include "MonsterInfoManager.h"
#include "GameScene.h"

void GameScene::AddStage1Data(void)
{
	MonsterSpawnManager::GetInstance()->AddSpawnData(STAGE1, BOSS, 1);
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
	//PlaneCamera* c = new PlaneCamera();
	AimPoint* ui = new AimPoint(L"AimPoint");
	LockPoint* ui2 = new LockPoint();
	Scene::AddGameObject(OBJ1, L"a", s);
	Engine::ObjectManager::GetInstance()->AddObjectAtLayer<Sea>(OBJ1, L"a");
	//Scene::AddGameObject(OBJ2, L"테스트", c);
	Scene::AddGameObject(UI, L"UI", ui);
	Scene::AddGameObject(UI, L"UI", ui2);
	Scene::AddGameObject(UI, L"UI", h);
	Scene::AddGameObject(OBJ2, L"테스트", t1);
	RadarPlane* radarplane = new RadarPlane();
	Scene::AddGameObject(UI, L"UI", radarplane);
	
	AddStage1Data();
	AddStage2Data();
	AddStage3Data();

	MonsterSpawnManager::GetInstance()->SpawnMonstersByData(stage);

	CameraManager::GetInstance()->AddCamera(CAM_PLAYER, new PlaneCamera());
	CameraManager::GetInstance()->AddCamera(CAM_CUTSCENE, new CutSceneCamera());
	CameraManager::GetInstance()->SetCamera(CAM_CUTSCENE);
	CameraManager::GetInstance()->SetCurrentCutScene(CUTSCENE_PLAYERDEAD);
}

void GameScene::Update(const FLOAT& dt)
{
	Engine::CollisionManager::GetInstance()->UpdateData();
	if (DXUTWasKeyPressed('P'))
		Engine::SceneManager::GetInstance()->SetScene(L"메뉴");

	if (DXUTWasKeyPressed('I'))
		CameraManager::GetInstance()->SetCamera(CAM_CUTSCENE);
	if (DXUTWasKeyPressed('J'))
		CameraManager::GetInstance()->SetCamera(CAM_PLAYER);

	if (CameraManager::GetInstance()->GetCurrentIndex() == CAM_CUTSCENE)
	{
		Engine::GameObject* cam = CameraManager::GetInstance()->GetCurrentCamera();
		if (dynamic_cast<CutSceneCamera*>(cam)->GetCutSceneIndex() == CUTSCENE_NONE)
		{
			CameraManager::GetInstance()->SetCamera(CAM_PLAYER);
		}
	}

	Scene::Update(dt);
	CameraManager::GetInstance()->UpdateCamera(dt);
}

void GameScene::LateUpdate(const FLOAT& dt)
{
	Engine::CollisionManager::GetInstance()->CheckCollision(PLAYER, MONSTER);
	Engine::CollisionManager::GetInstance()->CheckCollision(MISSILE, MONSTER);
	Engine::CollisionManager::GetInstance()->CheckCollision(PLAYER, MONSTERMISSILE);
	Scene::LateUpdate(dt);
	CameraManager::GetInstance()->LateUpdateCamera(dt);
}

void GameScene::Exit(void)
{
	Engine::CollisionManager::GetInstance()->ClearData();
	Engine::SubjectManager::GetInstance()->ClearObservers();
	Engine::GraphicsManager::GetInstance()->DeleteSprite();
	MonsterSpawnManager::GetInstance()->DeleteDatas();
	CameraManager::GetInstance()->DeleteCameraDatas();
	MonsterInfoManager::GetInstance()->DeleteTransformDatas();
	Scene::Exit();
}

void GameScene::Free(void)
{
	Scene::Free();
}
