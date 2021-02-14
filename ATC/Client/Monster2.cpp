#include "DXUT.h"
#include "Monster2.h"

Monster2::Monster2(void)
{

}

Monster2::~Monster2(void)
{
}

void Monster2::Movement(const FLOAT& dt)
{

}

INT Monster2::Update(const FLOAT& dt)
{
	MonsterBase::Update(dt);
	return OBJALIVE;
}

void Monster2::LateUpdate(const FLOAT& dt)
{
	MonsterBase::LateUpdate(dt);
}

void Monster2::Render(const FLOAT& dt)
{
	MonsterBase::Render(dt);
}

void Monster2::Free(void)
{
	MonsterBase::Free();
}
