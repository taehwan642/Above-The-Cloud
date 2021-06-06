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

namespace TEST
{
    LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL;
    LPDIRECT3DINDEXBUFFER9 g_pIB = NULL;
    struct CUSTOMVERTEX
    {
        FLOAT x, y, z;      // The untransformed, 3D position for the vertex
        DWORD color;        // The vertex color
    };
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)



    HRESULT Initialize(LPDIRECT3DDEVICE9 device)
    {
        // Initialize three vertices for rendering a triangle
        CUSTOMVERTEX g_Vertices[] =
        {
            { -1.0f, 1.0f, 0.0f, 0xffff0000, }, // 좌하단
            {  1.0f, 1.0f, 0.0f, 0xffffffff, }, // 좌상단
            {  1.0f,-1.0f, 0.0f, 0xff0000ff, }, // 우하단
            {  -1.0f, -1.0f, 0.0f, 0xffffffff, }, // 우상단
        };

        // Create the vertex buffer.
        if (FAILED(device->CreateVertexBuffer(4 * sizeof(CUSTOMVERTEX),
            0, D3DFVF_CUSTOMVERTEX,
            D3DPOOL_MANAGED, &g_pVB, NULL)))
        {
            return E_FAIL;
        }

        if (FAILED(device->CreateIndexBuffer(2 * sizeof(INDEX16), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED,
            &g_pIB, NULL)))
            return E_FAIL;

        // Fill the vertex buffer.
        VOID* pVertices;
        if (FAILED(g_pVB->Lock(0, sizeof(g_Vertices), (void**)&pVertices, 0)))
            return E_FAIL;
        memcpy(pVertices, g_Vertices, sizeof(g_Vertices));
        g_pVB->Unlock();

        INDEX16* pindex;
        if (FAILED(g_pIB->Lock(0, 0, (void**)&pindex, 0)))
            return E_FAIL;
        pindex[0]._0 = 0;
        pindex[0]._1 = 1;
        pindex[0]._2 = 2;

        pindex[1]._0 = 0;
        pindex[1]._1 = 2;
        pindex[1]._2 = 3;
        g_pIB->Unlock();
    }

    void Update(LPDIRECT3DDEVICE9 device)
    {
        // Turn off culling, so we see the front and back of the triangle
        device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

        // Turn off D3D lighting, since we are providing our own vertex colors
        device->SetRenderState(D3DRS_LIGHTING, FALSE);

        D3DXMATRIXA16 matWorld;

        UINT iTime = timeGetTime() % 1000;
        FLOAT fAngle = iTime * (2.0f * D3DX_PI) / 1000.0f;
        D3DXMatrixRotationY(&matWorld, fAngle);
        D3DXMATRIX matTrans;
        D3DXMatrixTranslation(&matTrans, 0, 0, 5);
        D3DXMATRIX res = matWorld * matTrans;
        device->SetTransform(D3DTS_WORLD, &res);

        //D3DXVECTOR3 vEyePt(0.0f, 3.0f, -5.0f);
        //D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
        //D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
        //D3DXMATRIXA16 matView;
        //D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
        //device->SetTransform(D3DTS_VIEW, &matView);

        device->SetStreamSource(0, g_pVB, 0, sizeof(CUSTOMVERTEX));
        device->SetFVF(D3DFVF_CUSTOMVERTEX);
        device->SetIndices(g_pIB);
        DEVICE->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
        //device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
        DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
    }

    void Close()
    {
        if (g_pVB != NULL)
            g_pVB->Release();
        if (g_pIB != NULL)
            g_pIB->Release();
    }
}




HRESULT CALLBACK OnD3D9CreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                     void* pUserContext )
{
    TEST::Initialize(pd3dDevice);
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
        //TEST::Update(pd3dDevice);
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

    TEST::Close();
}


//INT WINAPI wWinMain( HINSTANCE, HINSTANCE, LPWSTR, int )
int main(void)
{
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

    //_CrtSetBreakAlloc(1651);

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