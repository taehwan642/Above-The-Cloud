#include "DXUT.h"
#include "resource.h"
#include "Engine/SceneManager.h"
#include "Engine/ResourceManager.h"
#include "Engine/GraphicsManager.h"
#include "Engine/CollisionManager.h"
#include "Engine/SubjectManager.h"
#include "Engine/ObjectManager.h"
#include "Engine/RaycastManager.h"
#include "Engine/RenderManager.h"
#include "Client/MonsterSpawnManager.h"
#include "Client/CameraManager.h"
#include "Client/MonsterInfoManager.h"
#include "Client/GameScene.h"
#include "Client/MenuScene.h"
#include "Client/LoadScene.h"

HRESULT CALLBACK OnD3D9CreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                     void* pUserContext )
{
    srand(time(0));
    return S_OK;
}

HRESULT CALLBACK OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
    Engine::GraphicsManager::GetInstance()->ResetDevice();
    Engine::SceneManager::GetInstance()->ResetDevice();	
    return S_OK;
}

void CALLBACK OnFrameMove( double fTime, float fElapsedTime, void* pUserContext )
{
    if (DXUTWasKeyPressed('P'))
        Engine::SceneManager::GetInstance()->SetScene(L"메뉴");

    Engine::SceneManager::GetInstance()->SceneUpdate(fElapsedTime);
    Engine::SceneManager::GetInstance()->SceneLateUpdate(fElapsedTime);
}

void CALLBACK OnD3D9FrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
    HRESULT hr;

    V( pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB( 0, 45, 50, 170 ), 1.0f, 0 ) );

    if( SUCCEEDED( pd3dDevice->BeginScene() ) )
    {
        Engine::RenderManager::GetInstance()->RenderObject(fElapsedTime);
        V( pd3dDevice->EndScene() );
    }
    Engine::RenderManager::GetInstance()->ReleaseAllObjects();
}

LRESULT CALLBACK MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext)
{
    return 0;
}

void CALLBACK OnD3D9LostDevice( void* pUserContext )
{
    Engine::GraphicsManager::GetInstance()->LostDevice();
    Engine::SceneManager::GetInstance()->LostDevice();
}

void CALLBACK OnD3D9DestroyDevice( void* pUserContext )
{
    Engine::GraphicsManager::GetInstance()->DeleteSprite();
    Engine::GraphicsManager::DestroyInstance();

    Engine::SceneManager::GetInstance()->ReleaseScenes();
    Engine::SceneManager::DestroyInstance();

    Engine::ObjectManager::DestroyInstance();

    Engine::ResourceManager::GetInstance()->ReleaseResources();
    Engine::ResourceManager::DestroyInstance();

    Engine::CollisionManager::GetInstance()->ClearData();
    Engine::CollisionManager::DestroyInstance();
    
    MonsterSpawnManager::GetInstance()->DeleteDatas();
    MonsterSpawnManager::DestroyInstance();

    CameraManager::GetInstance()->DeleteCameraDatas();
    CameraManager::DestroyInstance();

    MonsterInfoManager::GetInstance()->DeleteTransformDatas();
    MonsterInfoManager::DestroyInstance();

    Engine::RenderManager::GetInstance()->ReleaseAllObjects();
    Engine::RenderManager::DestroyInstance();

    Engine::SubjectManager::GetInstance()->ClearObservers();
    Engine::SubjectManager::DestroyInstance();

    Engine::RaycastManager::DestroyInstance();

}


//INT WINAPI wWinMain( HINSTANCE, HINSTANCE, LPWSTR, int )
int main(void)
{
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    _CrtSetBreakAlloc(1651);

    DXUTSetCallbackD3D9DeviceCreated( OnD3D9CreateDevice );
    DXUTSetCallbackD3D9DeviceReset( OnResetDevice );
    DXUTSetCallbackFrameMove( OnFrameMove );
    DXUTSetCallbackD3D9FrameRender( OnD3D9FrameRender );
    DXUTSetCallbackMsgProc( MsgProc );
    DXUTSetCallbackD3D9DeviceLost( OnD3D9LostDevice );
    DXUTSetCallbackD3D9DeviceDestroyed( OnD3D9DestroyDevice );

    DXUTInit( true, true ); 
    DXUTSetHotkeyHandling( true, true, true ); 
    DXUTSetCursorSettings( true, true ); 
    DXUTCreateWindow( L"ATC" );
    DXUTCreateDevice( true, windowWidth, windowHeight );

    Engine::SceneManager::GetInstance()->AddScene(L"게임", new GameScene);
    Engine::SceneManager::GetInstance()->AddScene(L"로드", new LoadScene);
    Engine::SceneManager::GetInstance()->AddScene(L"메뉴", new MenuScene);
    Engine::SceneManager::GetInstance()->SetScene(L"로드");

    DXUTMainLoop();
    return DXUTGetExitCode();
}