#pragma once
#include "GameFlowState.h"

struct PlayerData
{
	float m_Score{ 0 };
	int m_Money{ 0 };
};

class MainGameState:public GameFlowState
{
private:


public:
	MainGameState(int levelNumber = 0);

	virtual ~MainGameState() override;

public:
	void OnEnter() override;

	void OnExit() override;

	GameFlowState* OnUpdate() override;

	inline static PlayerData& GetPlayerData()
	{
		static PlayerData playerData;
		return playerData;
	}

};

