#include "DXUT.h"
#include "AnimationController.h"
USING(Engine)

AnimationController::AnimationController(LPD3DXANIMATIONCONTROLLER _controller) :
    anicontroller(_controller),
    currentTrack(0),
    newTrack(1),
    accTime(0),
    oldAniIndex(4000)
{
    anicontroller->AddRef();
}

AnimationController::AnimationController(const AnimationController& cp) :
    currentTrack(cp.currentTrack),
    newTrack(cp.newTrack),
    accTime(cp.accTime),
    oldAniIndex(cp.oldAniIndex)
{
    cp.anicontroller->CloneAnimationController(cp.anicontroller->GetMaxNumAnimationOutputs(), 
                                               cp.anicontroller->GetMaxNumAnimationSets(), 
                                               cp.anicontroller->GetMaxNumTracks(), 
                                               cp.anicontroller->GetMaxNumEvents(), 
                                               &anicontroller);
}

AnimationController::~AnimationController(void)
{
}

void AnimationController::SetAnimationSet(const UINT& _index)
{
    if (oldAniIndex == _index)
        return;
    newTrack = (currentTrack == 0 ? 1 : 0);
    LPD3DXANIMATIONSET AS = nullptr;
    anicontroller->GetAnimationSet(_index, &AS);
    period = AS->GetPeriod();
    anicontroller->SetTrackAnimationSet(newTrack, AS);

    anicontroller->UnkeyAllTrackEvents(currentTrack);
    anicontroller->UnkeyAllTrackEvents(newTrack);

    anicontroller->KeyTrackEnable(currentTrack, FALSE, accTime + 0.25f);
    anicontroller->KeyTrackSpeed(currentTrack, 1, accTime, 0.25, D3DXTRANSITION_LINEAR);
    anicontroller->KeyTrackWeight(currentTrack, 0.1f, accTime, 0.25, D3DXTRANSITION_LINEAR);

    anicontroller->SetTrackEnable(newTrack, TRUE);
    anicontroller->KeyTrackSpeed(newTrack, 1, accTime, 0.25, D3DXTRANSITION_LINEAR);
    anicontroller->KeyTrackWeight(newTrack, 0.9f, accTime, 0.25, D3DXTRANSITION_LINEAR);
    ResetAnimation();
    oldAniIndex = _index;
    currentTrack = newTrack;
}

void AnimationController::ResetAnimation(void)
{
    anicontroller->ResetTime();
    accTime = 0;
    anicontroller->SetTrackPosition(newTrack, 0);
}

void AnimationController::PlayAnimation(const FLOAT& _dt)
{
    anicontroller->AdvanceTime(_dt, NULL);
    accTime += _dt;
}

bool AnimationController::IsAnimationEnd(void)
{
    D3DXTRACK_DESC trackInfo;
    ZeroMemory(&trackInfo, sizeof(D3DXTRACK_DESC));
    anicontroller->GetTrackDesc(currentTrack, &trackInfo);
    if (trackInfo.Position >= period - 0.01)
        return true;

    return false;
}

void AnimationController::Free(void)
{
    Safe_Release(anicontroller);
}
