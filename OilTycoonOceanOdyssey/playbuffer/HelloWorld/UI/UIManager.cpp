#include "UIManager.h"
#include "Button.h"
#include <string.h>
#include "../GameTool/DebugTool.h"

MouseState lyu_mouse;

void UIManager::CheckMouseIsOnUI()
{
	//check UI hover
	int btnCount = 0;
	for (auto& [id, element] : UIComponents_Map)
	{
		if (element.OnHover())
		{
			lyu_mouse.isOnUI = true;
			btnCount++;
		}
	}
	if (btnCount == 0)
		lyu_mouse.isOnUI = false;
}

UIManager& UIManager::GetInstance()
{
	static UIManager _instance;
	return _instance;
}

void UIManager::AddNewUIElement(UIElement& component)
{
	UIComponents_Map[component.GetID()] = component;
}

void UIManager::DrawUIElements()
{
	for (auto& [id, element] : UIComponents_Map)
	{
		element.Render();
	}
}

void UIManager::UIInitialize()
{
	using namespace Play;

}

void UIManager::CheckUIEvent()
{
	for (auto& [id, element] : UIComponents_Map)
	{
		element.OnDrag();
		element.OnClick();
	}
}