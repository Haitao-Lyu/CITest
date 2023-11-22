#include "OilChunk.h"
#include "GameState/MainGameState.h"
#include "Level/LevelMgr.h"
#include "Level/Level.h"
#include "GameTool/Timer.h"
#include "GameObjectMgr.h"
#include "OilPlatform.h"

OilChunk::OilChunk(Play::Point2D pos, E_OilChunk size /*= E_OilChunk::SMALL*/) :GameObject(pos, E_OBJTYPE::E_OILCHUNK)
{
	m_size = size;
	switch (m_size)
	{
	case E_OilChunk::SMALL:
		spriteName = "oilSmall";
		m_OilNum = 10;
		m_OriginOilNum = 10;
		break;
	case E_OilChunk::MEDIUM:
		spriteName = "oilMedium";
		m_OilNum = 20;
		m_OriginOilNum = 20;
		break;
	case E_OilChunk::LARGE:
		spriteName = "oilLarge";
		m_OilNum = 30;
		m_OriginOilNum = 30;
		break;
	default:
		break;
	}
}

OilChunk::~OilChunk()
{

}

void OilChunk::Update()
{
	if(isRevealed)
	Render();
}

void OilChunk::Render()
{
	Play::DrawSpriteRotated(Play::GetSpriteId(spriteName), m_pos, 0, 0, m_scale);

}

void OilChunk::BeSucked(bool isiSuckReachTop, OilPlatform* Pplatform)
{
	if (!isiSuckReachTop)
		return;
	PlayerData& data = MainGameState::GetPlayerData();
	Level* lev = LevelMgr::GetInstance()->GetCurrentLevel();

	Pplatform->m_capacity += Timer::DeltaTime() * m_drainedSpeed;

	m_OilNum -= Timer::DeltaTime() * m_drainedSpeed;
	lev->m_currenyStorage += Timer::DeltaTime() * m_drainedSpeed;
	data.m_Score += Timer::DeltaTime() * m_drainedSpeed * 10;

	m_scale = (float)m_OilNum / (float)m_OriginOilNum;

	if (m_scale <= 0.2f)
	{
		lev->m_currenyStorage += m_scale * m_OilNum;
		data.m_Score += m_scale * m_OilNum * 10;
		m_scale = 0;
		isEmpty = true;
		//GameObjectMgr::RemoveGameObject(*this);
	}
}
