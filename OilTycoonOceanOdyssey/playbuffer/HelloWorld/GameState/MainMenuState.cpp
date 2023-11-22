#include "Play.h"
#include "MainMenuState.h"
#include "MainGameState.h"
#include "GameObjectMgr.h"
#include "UI/UIManager.h"
#include "GameObject/SubMarine.h"

MainMenuState::MainMenuState()
{

}

MainMenuState::~MainMenuState()
{
	OnDestroy();
}

void MainMenuState::OnEnter()
{
	GameObjectMgr::MakeSubMarine(Play::Vector2f{ DISPLAY_WIDTH / 3, DISPLAY_HEIGHT/2  }, E_SubMarine::SMALL);
}


GameFlowState* MainMenuState::OnUpdate()
{
	Play::Colour color{ 9.0f, 31.f, 50.f};
	Play::ClearDrawingBuffer(color);
	Play::DrawDebugText({ 192 / 2, 160 / 2 - 20 }, "Oil Tycoon: Ocean Odyssey!");
	Play::DrawDebugText({ 192 / 2, 160 / 2 }, "Press space to start!");

	GameObjectMgr::UpdateGameObjectsByType(E_OBJTYPE::E_Submarine);

	if(Play::KeyPressed(VK_SPACE))
	{
		return new MainGameState();
	}
	return nullptr;
}


void MainMenuState::OnExit()//Don't touch memory in Logic Exit
{
	GameObjectMgr::ClearAllGameobjects();
}

void MainMenuState::OnDestroy()
{

}
