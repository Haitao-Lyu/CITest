#include "ApplicationMgr.h"
#include "../GameState/MainMenuState.h"
namespace ApplicationMgr
{
	static GameFlowState* m_gameState = nullptr;

	static int intialLevel = 0;

	void Update()
	{
		if (!m_gameState)
		{
			m_gameState = new MainMenuState();
			m_gameState->OnEnter();
		}

		GameFlowState* newState = m_gameState->OnUpdate();
		if (newState != nullptr)
		{
			m_gameState->OnExit();
			delete m_gameState;
			m_gameState = newState;
			m_gameState->OnEnter();
		}
	}

	void Destroy()
	{
		if (m_gameState)
		{
			delete m_gameState;
			m_gameState = nullptr;
		}
	}
	
}


