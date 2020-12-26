#include "DXUT.h"
#include "Observer.h"
#include "Subject.h"

USING(Engine)
void Subject::Subscribe(Observer* _observer)
{
	observergroup.push_back(_observer);
}

void Subject::UnSubscribe(Observer* _observer)
{
	auto iter = observergroup.begin();
	auto iterend = observergroup.end();

	for (; iter != iterend;)
	{
		if ((*iter) == _observer)
		{
			observergroup.erase(iter);
			return;
		}
		else
			++iter;
	}
}

void Subject::Notify(UINT _flag)
{
	for (auto& iter : observergroup)
		iter->UpdateObserver(_flag);
}

void Subject::Free(void)
{
	observergroup.clear();
}
