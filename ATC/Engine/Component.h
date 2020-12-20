#pragma once
#include "Base.h"
NAMESPACE(Engine)
class Component :
    public Base
{
private:
protected:
public:
    explicit Component(void) {};
    virtual ~Component(void) {};

    virtual void ResetDevice(void) {};
    virtual void LostDevice(void) {};

    virtual void Update(const FLOAT& dt) {};
    virtual void Render() {};
};
END
