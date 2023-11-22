#define PLAY_USING_GAMEOBJECT_MANAGER
#include "GameState/ApplicationMgr.h"
#include "Play.h"
#include "GameTool/Timer.h"

int DISPLAY_WIDTH = 192;
int DISPLAY_HEIGHT = 160;
int DISPLAY_SCALE = 5;

// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	Timer::UpdateDeltaTime(elapsedTime);
	ApplicationMgr::Update();

	Play::PresentDrawingBuffer();
	return false;
}

// Gets called once when the player quits the game 
int MainGameExit( void )
{
	Play::DestroyManager();
	return PLAY_OK;
}

