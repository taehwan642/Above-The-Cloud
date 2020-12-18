#pragma once
#include "Component.h"

NAMESPACE(Engine)
class Resources :
    public Component
{
    explicit Resources(void) {};
    virtual ~Resources(void) {};

    virtual Resources* Clone(void) PURE;
};
END
