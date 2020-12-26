#include "DXUT.h"
#include "resource.h"
#include "Engine/SceneManager.h"
#include "Engine/ResourceManager.h"
#include "Client/MenuScene.h"

HRESULT CALLBACK OnD3D9CreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                     void* pUserContext )
{

    return S_OK;
}

HRESULT CALLBACK OnResetDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
    Engine::SceneManager::GetInstance()->ResetDevice();	
    DEVICE->SetRenderState(D3DRS_LIGHTING, false);
    DEVICE->LightEnable(0, false);
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
    Engine::SceneManager::GetInstance()->LostDevice();
}

void CALLBACK OnD3D9DestroyDevice( void* pUserContext )
{
    exit(1);
}


//INT WINAPI wWinMain( HINSTANCE, HINSTANCE, LPWSTR, int )
int main(void)
{
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

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


