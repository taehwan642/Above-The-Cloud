#include "DXUT.h"
#include "Base.h"

USING(Engine)

ULONG Base::GetRefCount(void) const
{
	return refCount;
}

ULONG Base::AddReference(void)
{
	return refCount++;
}

ULONG Base::Release(void)
{
	if (refCount == 0)
	{
		Free();
		delete this;
		return 0;
	}
	return refCount--;
}
