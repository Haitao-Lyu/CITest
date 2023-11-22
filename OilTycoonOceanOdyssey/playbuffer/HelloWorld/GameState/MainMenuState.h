#pragma once
#include "GameFlowState.h"

class MainMenuState :public GameFlowState
{
private:


public:

	MainMenuState();

	virtual ~MainMenuState() override;

	void OnEnter() override;

	void OnExit() override;

	void OnDestroy();

	GameFlowState* OnUpdate() override;

};