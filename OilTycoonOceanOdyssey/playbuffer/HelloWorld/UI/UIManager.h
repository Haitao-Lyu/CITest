#pragma once
#include "UIElement.h"
#include <map>

#define DISPLAY_HEIGHT 192
#define DISPLAY_WIDTH 160

struct MouseState
{
	bool isOnUI = false;
};

class UIManager
{
private:
	//vector can only hold same size in consistent
	//static related to class not entity
	std::map<int,UIElement> UIComponents_Map;//base class must be pointer or reference
private:
	UIManager() {}

	UIManager(const UIManager& instance) = delete;

	UIManager& operator=(UIManager& instance) = delete;	

	void CheckMouseIsOnUI();
public:
	static UIManager& GetInstance();

	void AddNewUIElement(UIElement& component);

	void UIInitialize();

	void DrawUIElements();

	void CheckUIEvent();
};

