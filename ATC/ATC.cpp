#include "DXUT.h"
#include "resource.h"
#include "Engine/SceneManager.h"
#include "Engine/ResourceManager.h"
#include "Engine/GraphicsManager.h"
#include "Engine/CollisionManager.h"
#include "Engine/EffectManager.h"
#include "Engine/SubjectManager.h"
#include "Engine/ObjectManager.h"
#include "Client/MenuScene.h"




HRESULT CALLBACK OnD3D9CreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                     void* pUserContext )
{

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
        Engine::SceneManager::GetInstance()->SceneRender(fElapsedTime);
        V( pd3dDevice->EndScene() );
    }
}

void CALLBACK OnD3D9LostDevice( void* pUserContext )
{
    Engine::GraphicsManager::GetInstance()->LostDevice();
    Engine::SceneManager::GetInstance()->LostDevice();
}

void CALLBACK OnD3D9DestroyDevice( void* pUserContext )
{
    Engine::GraphicsManager::GetInstance()->DeleteSprite();
    Engine::GraphicsManager::GetInstance()->DestroyInstance();

    Engine::SceneManager::GetInstance()->ReleaseScenes();
    Engine::SceneManager::GetInstance()->DestroyInstance();

    Engine::ObjectManager::GetInstance()->DestroyInstance();

    Engine::ResourceManager::GetInstance()->ReleaseResources();
    Engine::ResourceManager::GetInstance()->DestroyInstance();

    Engine::CollisionManager::GetInstance()->ClearData();
    Engine::CollisionManager::GetInstance()->DestroyInstance();
    
    Engine::EffectManager::GetInstance()->DestroyInstance();

    Engine::SubjectManager::GetInstance()->ClearObservers();
    Engine::SubjectManager::GetInstance()->DestroyInstance();

    cout << "ALL DELETED" << endl;
    exit(1);
}


//INT WINAPI wWinMain( HINSTANCE, HINSTANCE, LPWSTR, int )
int main(void)
{
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    //_CrtSetBreakAlloc(252);

    DXUTSetCallbackD3D9DeviceCreated( OnD3D9CreateDevice );
    DXUTSetCallbackD3D9DeviceReset( OnResetDevice );
    DXUTSetCallbackD3D9FrameRender( OnD3D9FrameRender );
    DXUTSetCallbackD3D9DeviceLost( OnD3D9LostDevice );
    DXUTSetCallbackD3D9DeviceDestroyed( OnD3D9DestroyDevice );
    DXUTSetCallbackFrameMove( OnFrameMove );

    DXUTInit( true, true ); 
    DXUTSetHotkeyHandling( true, true, true ); 
    DXUTSetCursorSettings( true, true ); 
    DXUTCreateWindow( L"ATC" );
    DXUTCreateDevice( true, windowWidth, windowHeight );

    Engine::SceneManager::GetInstance()->AddScene(L"메뉴", new MenuScene);
    Engine::SceneManager::GetInstance()->SetScene(L"메뉴");

    DXUTMainLoop();
    return DXUTGetExitCode();
}


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG