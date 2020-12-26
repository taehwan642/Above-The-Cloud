#pragma once
#include "Base.h"

NAMESPACE(Engine)
class Observer :
    public Base
{
private:
protected:
    explicit Observer(void) {};
public:
    virtual ~Observer(void) {};

    virtual void UpdateObserver(UINT _flag) PURE;
    void Free(void) override {};
};
END
