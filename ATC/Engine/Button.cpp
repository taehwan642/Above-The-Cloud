#include "DXUT.h"
#include "Button.h"
USING(Engine)
Button::Button(void) :
	DynamicUI(L"", false)
{
}

Button::Button(const std::wstring& _texturetag) :
	DynamicUI(_texturetag)
{

}

Button::~Button(void)
{
}

INT Button::Update(const FLOAT& dt)
{
	return DynamicUI::Update(dt);
}

void Button::LateUpdate(const FLOAT& dt)
{
	DynamicUI::LateUpdate(dt);
}

void Button::Render(const FLOAT& dt)
{
	DynamicUI::Render(dt);
}

void Button::SetButtonFunction(std::function<void(void)> _function)
{
	buttonFunction = _function;
}

std::function<void(void)> Button::GetButtonFunction(void) const
{
	return buttonFunction;
}

void Button::Free(void)
{
	DynamicUI::Free();
}
