#include "DXUT.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Layer.h"
#include "test.h"
#include "Camera.h"
#include "MenuScene.h"


void MenuScene::Start(void)
{
	if (SUCCEEDED(Engine::ResourceManager::GetInstance()->AddMesh(MeshType::STATIC, L"Resources/Meshes/Static/", L"Item (1).x", L"test")))
		cout << "히히메시잘불러와져땅" << endl;
	if (SUCCEEDED(Engine::ResourceManager::GetInstance()->AddMesh(MeshType::DYNAMIC, L"Resources/Meshes/Dynamic/", L"testdoubleanimation.x", L"dynamic")))
		cout << "다이나믹메시불러와짐" << endl;
	//if (SUCCEEDED(Engine::ResourceManager::GetInstance()->AddShader(L"Resources/Shaders/DefaultShader.fx", L"shader")))
	//	cout << "Shader Load Complete" << endl;
	if (SUCCEEDED(Engine::ResourceManager::GetInstance()->AddShader(L"Resources/Shaders/DynamicMeshShader.fx", L"dyshader")))
		cout << "dyShader Load Complete" << endl;

	Engine::Layer* l = new Engine::Layer();
	layergroup.emplace(L"테스트", l);
	test* t = new test();
	Camera* c = new Camera();
	Scene::AddGameObject(L"테스트", L"테스트", t);
	Scene::AddGameObject(L"테스트", L"테스트", c);
	
}

void MenuScene::Update(const float& dt)
{
	//D3DXVECTOR3 vEyePt(0.0f, 0.0f, -0.5f);
	//D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
	//D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	//D3DXMATRIXA16 matView;
	//D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	//DEVICE->SetTransform(D3DTS_VIEW, &matView);
	//
	//D3DXMATRIXA16 matProj;
	//D3DVIEWPORT9 viewPort;
	//DEVICE->GetViewport(&viewPort);
	//D3DXMatrixPerspectiveFovLH(&matProj, D3DXToRadian(60.f), viewPort.Width / (float)viewPort.Height, 0.1f, 1500.f);
	//DEVICE->SetTransform(D3DTS_PROJECTION, &matProj);
	Scene::Update(dt);
}

void MenuScene::LateUpdate(void)
{
	
	Scene::LateUpdate();
}

void MenuScene::Render(void)
{
	Scene::Render();
}

void MenuScene::Exit(void)
{
	cout << "엑시트" << endl;
	Scene::Exit();
}

void MenuScene::Free(void)
{
	Scene::Free();
}
