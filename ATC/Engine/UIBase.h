#pragma once
#include "GameObject.h"

NAMESPACE(Engine)
class Transform;
class Texture;
class UIBase :
    public GameObject
{
private:
protected:
    D3DXVECTOR2 pivot = { 0.5f,0.5f };
    Transform* transform = nullptr;
    Texture* texture = nullptr;
    UINT currentTextureindex = 0;
public:
    // 1. 렌더는 가장 첫번째
    // 2. front를 뽑아와서 빌보드 변환
    // 3. Non-Cull 필요
    
    // Sprite Create할때 복사 확인 필요 (복사 안하면 Constructer에, 하면 Singleton으로 RenderManager에)!
    // UI포지션 설정 필요 Transform
    
    // UI가 필요한것들
    // 1. 위치
    // 2. RHW || Billboard
    // 3. Render방식 (Non-Effect || Effect)
    // 4. UI Animation
    // 5. UI Clipping Bound (For HP bar and others)

    // 렌더할때 memcpy로 8byte만큼만 때려넣으면 될듯 (위치).
    
    // Aimpoint는 Billboard로 2D -> 3D 좌표 변환 시켜서 Forward방향에 띄워주면 될듯? 아마도 
    
    explicit UIBase(void);
    explicit UIBase(wstring _texturetag);
    virtual ~UIBase(void);

    void SetUITexture(const UINT& _index);
    
    void Update(const FLOAT& dt) override;
    void LateUpdate(const FLOAT& dt) override;
    void Render(const FLOAT& dt) override;

    void Free(void) override;
};
END
