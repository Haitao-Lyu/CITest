#include "MainGameState.h"
#include "Play.h"
#include "MainMenuState.h"
#include "../UI/UIManager.h"
#include "GameObjectMgr.h"
#include "GameObject/OilPlatform.h"
#include "GameObject/OilChunk.h"
#include "Level/LevelMgr.h"
#include "GameTool/DebugTool.h"

MainGameState::MainGameState(int levelNumber)
{
	
}


MainGameState::~MainGameState()
{
	
}

void MainGameState::OnEnter()
{
	Play::LoadBackground("Data\\Backgrounds\\oceanBK.png");
	Play::CentreAllSpriteOrigins();

	Level Level1;
	Level1.m_smallPlatform = 2;
	Level1.m_mediumPlatform = 2;
	Level1.m_LargePlatform = 2;
	Level1.m_detectionToool = 4;
	Level1.m_RescuShip = 0;	
	Level1.m_maxCapacity = 15;	
	
	Level Level2;
	Level2.m_smallPlatform = 2;
	Level2.m_mediumPlatform = 1;
	Level2.m_LargePlatform = 1;
	Level2.m_detectionToool = 3;
	Level2.m_RescuShip = 0;
	Level2.m_maxCapacity = 30;	
	
	Level Level3;
	Level3.m_smallPlatform = 2;
	Level3.m_mediumPlatform = 1;
	Level3.m_LargePlatform = 1;
	Level3.m_detectionToool = 3;
	Level3.m_RescuShip = 0;
	Level3.m_maxCapacity = 45;	
	
	Level Level4;
	Level4.m_smallPlatform = 1;
	Level4.m_mediumPlatform = 1;
	Level4.m_LargePlatform = 1;
	Level4.m_detectionToool = 3;
	Level4.m_RescuShip = 0;
	Level4.m_maxCapacity = 60;

	LevelMgr::GetInstance()->AddNewLevel(Level1);
	LevelMgr::GetInstance()->AddNewLevel(Level2);
	LevelMgr::GetInstance()->AddNewLevel(Level3);
	LevelMgr::GetInstance()->AddNewLevel(Level4);


}

GameFlowState* MainGameState::OnUpdate()
{
	using namespace Play;
	Play::DrawBackground();

	GameObjectMgr::UpdateGameObjectsByType(E_OBJTYPE::E_Submarine);
	GameObjectMgr::UpdateGameObjectsByType(E_OBJTYPE::E_OILPLATFORM);
	GameObjectMgr::UpdateGameObjectsByType(E_OBJTYPE::E_OILCHUNK);

	LevelMgr::GetInstance()->Update();


	PlayerData& data = MainGameState::GetPlayerData();
	Level* lev = LevelMgr::GetInstance()->GetCurrentLevel();
	DebugValue((int)data.m_Money, "Profit:", 0.0f, Play::cYellow, 110.f);
	DebugValue((int)lev->m_currenyStorage, "OIL:", 14, Play::cYellow, 110.f);
	DebugValue((int)lev->m_maxCapacity, "Target:", 28, Play::cYellow, 110.f);
	DebugValue((int)lev->m_smallPlatform, "SmlRig:", 0, Play::cYellow, 20.f);
	DebugValue((int)lev->m_mediumPlatform, "MedRig:", 14, Play::cYellow, 20.f);
	DebugValue((int)lev->m_LargePlatform, "LrgRig:", 28, Play::cYellow, 20.f);
	DebugValue((int)lev->m_detectionToool, "Radar:", 42, Play::cYellow, 20.f);

	if (Play::KeyPressed(VK_ESCAPE))
	{
		return new MainMenuState();
	}
	return nullptr;

}

void MainGameState::OnExit()
{
	GameObjectMgr::ClearAllGameobjects();
	Level* lev = LevelMgr::GetInstance()->GetCurrentLevel();
	lev->Clear();
	LevelMgr::GetInstance()->ClearAllLevel();
}
