#include "Play.h"
#include "Level.h"
#include "GameObject.h"
#include "GameObjectMgr.h"
#include "GameObject/OilPlatform.h"
#include "GameObject/OilChunk.h"
#include "GameObject/SubMarine.h"
#include "UI/UIManager.h"
#include "GameTool/DebugTool.h"
#include "GameState/MainGameState.h"

Level::Level()
{

}

Level::~Level()
{
	Destroy();
}

#define oilrandX 5
#define oilrandY 5

static int randomOilX[oilrandX] = { 20, 60, 100, 140, 160 };
static int randomOilY[oilrandY] = { 148, 146, 150, 145, 152 };

static Play::Vector2f randomPos[oilrandX] = { {20,148}, {60,146},{100,150},{140,145}, {160, 152} };

void Level::OnEnter()
{
	using namespace Play;
	GameObjectMgr::MakeOilChunk(Vector2f{ randomOilX[rand() % oilrandX], randomOilY[rand() % oilrandY] }, E_OilChunk::SMALL);
	GameObjectMgr::MakeOilChunk(Vector2f{ randomOilX[rand() % oilrandX], randomOilY[rand() % oilrandY] }, E_OilChunk::MEDIUM);
	GameObjectMgr::MakeOilChunk(Vector2f{ randomOilX[rand() % oilrandX], randomOilY[rand() % oilrandY] }, E_OilChunk::LARGE);
	GameObjectMgr::MakeOilChunk(Vector2f{ randomOilX[rand() % oilrandX], randomOilY[rand() % oilrandY] }, E_OilChunk::SMALL);
	GameObjectMgr::MakeOilChunk(Vector2f{ randomOilX[rand() % oilrandX], randomOilY[rand() % oilrandY] }, E_OilChunk::SMALL);

	pSubmarin = GameObjectMgr::MakeSubMarine(Vector2f{ randomOilX[rand() % oilrandX], randomOilY[rand() % oilrandY] }, E_SubMarine::SMALL);

	//GameObjectMgr::MakeOilChunk(randomPos[rand() % oilrandX], E_OilChunk::SMALL);
	//GameObjectMgr::MakeOilChunk(randomPos[rand() % oilrandX], E_OilChunk::MEDIUM);
	//GameObjectMgr::MakeOilChunk(randomPos[rand() % oilrandX], E_OilChunk::LARGE);
	//GameObjectMgr::MakeOilChunk(randomPos[rand() % oilrandX], E_OilChunk::SMALL);
	//GameObjectMgr::MakeOilChunk(randomPos[rand() % oilrandX], E_OilChunk::SMALL);

}

static GameObject* pMouseObj = nullptr;

void Level::PlaceTheOilPlatform()
{
	using namespace Play;

	static int g_platformUpper = 58;
	static int g_platformBottom = 62;

	//Chose Platform to Place
	Vector2f spawnPos{ -100.0f, -100.0f };
	if (pSubmarin)
		spawnPos = pSubmarin->GetPosition();
	if (Play::KeyPressed(VK_NUMPAD5))
	{
		if (pSubmarin)
		{
			if (pSubmarin->m_size == E_SubMarine::SMALL)
			{
				pSubmarin->m_size = E_SubMarine::MEDIUM;
			}		
			else
			{
				pSubmarin->m_size = E_SubMarine::SMALL;
			}
		}
	}

	if (Play::KeyPressed(0x31) && m_smallPlatform > 0)//key 1
	{
		if (pMouseObj)
		{
			GameObjectMgr::RemoveGameObjectByid(pMouseObj->GetID());
			pMouseObj = nullptr;
		}
		pMouseObj = GameObjectMgr::MakeOilPlatform(spawnPos, E_OilPlatformSize::SMALL);

	}
	if (Play::KeyPressed(0x32) && m_mediumPlatform > 0)//key 2
	{
		if (pMouseObj)
		{
			GameObjectMgr::RemoveGameObjectByid(pMouseObj->GetID());
			pMouseObj = nullptr;
		}
		pMouseObj = GameObjectMgr::MakeOilPlatform(spawnPos, E_OilPlatformSize::MEDIUM);
	}
	if (Play::KeyPressed(0x33) && m_LargePlatform > 0)//key 3
	{
		if (pMouseObj)
		{
			GameObjectMgr::RemoveGameObjectByid(pMouseObj->GetID());
			pMouseObj = nullptr;
		}
		pMouseObj = GameObjectMgr::MakeOilPlatform(spawnPos, E_OilPlatformSize::LARGE);
	}

	if (Play::KeyPressed(0x45))//key E
	{
		if (pMouseObj)
		{
			OilPlatform* pPlatform = static_cast<OilPlatform*>(pMouseObj);
			switch (pPlatform->m_size)
			{
			case E_OilPlatformSize::SMALL:
				m_smallPlatform--;
				break;
			case E_OilPlatformSize::MEDIUM:
				m_mediumPlatform--;
				break;
			case E_OilPlatformSize::LARGE:
				m_LargePlatform--;
				break;
			default:
				break;
			}
			pPlatform->m_isDrilling = true;
		}
		pMouseObj = nullptr;
	}
	else
	{
		if (pMouseObj)
		{
			float clipY = spawnPos.y > g_platformUpper ? g_platformUpper : spawnPos.y;
			clipY = clipY < g_platformBottom ? g_platformBottom : clipY;

			Vector2f clipPos{ (int)((int)spawnPos.x / 4) * 4, clipY };
			pMouseObj->SetPosition(clipPos);
		}
	}
}

void Level::Update()
{
	PlaceTheOilPlatform();

	if (m_currenyStorage > m_maxCapacity)
	{
		DebugText("Well Done! Press 'P' CONTINUE", Play::Point2D{DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2}, Play::cBlack);

		PlayerData& data = MainGameState::GetPlayerData();

		data.m_Money = (m_currenyStorage - m_maxCapacity) * 18.0f;

		if (Play::KeyPressed(0x50))
		{
			isEnd = true;
		}
	}
	else
	{
		
		PlayerData& data = MainGameState::GetPlayerData();
		data.m_Money = (m_currenyStorage - m_maxCapacity) * 18.0f;
	}
}

void Level::OnExit()
{
	Clear();
}

//clear the resources doesn't related to heap
void Level::Clear()
{
	if (pMouseObj)
	{
		GameObjectMgr::RemoveGameObjectByid(pMouseObj->GetID());
		pMouseObj = nullptr;
	}

	GameObjectMgr::ClearAllGameobjects();
}

//when exit it's already destroyed
void Level::Destroy()
{

}

bool Level::isLevelEnd()
{
	return isEnd;
}
