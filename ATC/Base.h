#pragma once

NAMESPACE(Engine)
class Base
{
private:
protected:
	ULONG refCount = 0;
	explicit Base(void) : refCount(0) {};
	virtual ~Base(void) {};
	virtual void Free(void) PURE;
public:
	ULONG AddReference(void);
	ULONG Release(void);
};
END

