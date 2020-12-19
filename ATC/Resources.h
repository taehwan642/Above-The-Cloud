#pragma once
#include "Component.h"

NAMESPACE(Engine)
class Resources :
    public Component
{
public:
    explicit Resources(void) {};
    virtual ~Resources(void) {};

    virtual Resources* Clone(void) PURE;

    void Free(void) override {};
};
END
