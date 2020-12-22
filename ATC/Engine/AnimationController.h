#pragma once
#include "Base.h"
NAMESPACE(Engine)
class AnimationController final :
	public Base
{
private:
	LPD3DXANIMATIONCONTROLLER anicontroller;
	UINT					  currentTrack;
	UINT				      newTrack;
	FLOAT                     accTime;
	UINT                      oldAniIndex;
	DOUBLE                    period;
protected:
public:
	explicit AnimationController(LPD3DXANIMATIONCONTROLLER _controller);
	explicit AnimationController(const AnimationController& cp);
	virtual  ~AnimationController(void);

	LPD3DXANIMATIONCONTROLLER GetController(void) { return anicontroller; }
	UINT GetCurrentTrackIndex(void) { return currentTrack; }
	UINT GetNewTrackIndex(void) { return newTrack; }
	DOUBLE GetPeriod(void) { return period; }
	FLOAT GetAccTime(void) { return accTime; }

	void SetAnimationSet(const UINT& _index);
	void ResetAnimation(void);
	void PlayAnimation(const FLOAT& _dt);
	bool IsAnimationEnd(void);

	void Free(void) override;
};
END
