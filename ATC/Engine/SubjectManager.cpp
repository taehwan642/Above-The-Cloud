#include "DXUT.h"
#include "SubjectManager.h"

USING(Engine)
void SubjectManager::AddData(UINT _flag, void* _data)
{
	auto iter = datagroup.find(_flag);
	if (iter == datagroup.end())
	{
		datagroup.emplace(_flag, _data);
		Notify(_flag);
	}
}

void SubjectManager::DeleteData(UINT _flag)
{
	auto iter = datagroup.find(_flag);
	if (iter != datagroup.end())
		datagroup.erase(_flag);
}

void* SubjectManager::GetData(UINT _flag)
{
	auto iter = datagroup.find(_flag);
	if (iter != datagroup.end())
		return iter->second;
	return nullptr;
}

void SubjectManager::ClearObservers(void)
{
	Subject::Free();
}
