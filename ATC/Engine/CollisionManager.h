#pragma once
#include "Singleton.h"
NAMESPACE(Engine)
class CollisionManager :
    public Singleton<CollisionManager>
{
    // 1. 살아있는 모든 적 (총알 포함) 게임오브젝트들의 콜라이더를 플레이어와 체크해서 Bound 안에 들어왔다 하면 데미지 입히기
    // 그러려면 뭐가 있어야하지? 1. IsHit같은 bool형태 변수 하나로 player속에서 if(CM::GINS()->isHit()) hp--; 이런거 해야할듯
    // 또 list로 모든 게임오브젝트들의 collider 정보들을 담고있어야할듯 실시간으로 삭제되게 해야할것같은데 좀 봐야할듯
    // 아 GameObject에 Collider정보를 가지고있고
    // 그 Collider정보만 가지고 있다가 물체가 삭제될때 그에 해당하는 collider번호만 삭제시켜주는 식으로 하면 될듯
    // 그럼 DeleteColliderData(번호)
    // map[번호(list)].clear()?

    // map value == list로 key == ENUM 으로 하고
    // 그냥 업데이트 맨 위에서 돌리면 될듯
};
END