#pragma once
#include "Base.h"

NAMESPACE(Engine)
class Observer;
class Subject :
    public Base
{
private:
protected:
    list<Observer*> observergroup;
public:
    explicit Subject(void) {};
    virtual ~Subject(void) {};

    virtual void Subscribe(Observer* _observer);
    virtual void UnSubscribe(Observer* _observer);
    virtual void Notify(UINT _flag);

    void Free(void) override;
};
END