#include "SubMarine.h"
#include "UI/UIManager.h"
#include "GameObjectMgr.h"
#include "OilChunk.h"
#include "GameTool/Timer.h"
#include "Level/LevelMgr.h"
#include "Level/Level.h"

SubMarine::SubMarine(Play::Point2D pos, E_SubMarine size /*= E_SubMarine::SMALL*/): GameObject(pos, E_OBJTYPE::E_Submarine)
{
	m_size = size;
	switch (m_size)
	{
	case E_SubMarine::SMALL:
		spriteName = "subSmall";
		m_revealDis = 30;
		break;
	case E_SubMarine::MEDIUM:
		spriteName = "subLarge";
		m_revealDis = 50;
		break;
	default:
		break;
	}
}

SubMarine::~SubMarine()
{

}


void SubMarine::SwitchType()
{
	switch (m_size)
	{
	case E_SubMarine::SMALL:
		spriteName = "subSmall";
		m_revealDis = 30;
		break;
	case E_SubMarine::MEDIUM:
		spriteName = "subLarge";
		m_revealDis = 50;
		break;
	default:
		break;
	}
}


void SubMarine::InputHandle()
{
	using namespace Play;
	static int seaLevel = 100;
	static int soilGround = 165;
	static int padding = 2;

	if (KeyDown(VK_UP))
	{
		m_pos.y -= 1.0f;
		if (m_pos.y <= seaLevel + padding)
		{
			m_pos.y = seaLevel + padding;
		}
	}
	if (KeyDown(VK_DOWN))
	{
		m_pos.y += 1.0f;
		if (m_pos.y >= soilGround - padding)
		{
			m_pos.y = soilGround - padding;
		}
	}
	if (KeyDown(VK_LEFT))
	{
		m_pos.x -= 1.0f;
		if (m_pos.x <= 0 + padding)
		{
			m_pos.x = 0 + padding;
		}
		m_scaleX = -1;

	}
	if (KeyDown(VK_RIGHT))
	{
		m_pos.x += 1.0f;
		if (m_pos.x >= 192 - padding)
		{
			m_pos.x = 192 - padding;
		}
		m_scaleX = 1;
		m_rot = 0;
	}
	SwitchType();
	Level* lev = LevelMgr::GetInstance()->GetCurrentLevel();
	if(lev)
	if (KeyPressed(VK_SPACE) && lev->m_detectionToool > 0)
	{
		m_isRevealing = true;
		m_revealAnim = m_revealDis;
		m_animCounter = 0.0f;
		lev->m_detectionToool--;
	}
}


void SubMarine::OilDetection()
{

	std::vector<GameObject*>& objs = GameObjectMgr::GetGameObjectsByType(E_OBJTYPE::E_OILCHUNK);

	for (GameObject* obj : objs)
	{
		float distance = Play::length(obj->m_pos - m_pos);
		if (distance <= m_revealDis)
		{

			OilChunk* pChunk = reinterpret_cast<OilChunk*>(obj);

			pChunk->isRevealed = true;
		}
	}
}

void SubMarine::Update()
{
	using namespace Play;
	if(!m_isRevealing)
	InputHandle();
	else
	OilDetection();


	Render();
}

void SubMarine::Render()
{
	Play::Matrix2D rotMt = Play::MatrixRotation(Play::DegToRad(m_rot));
	const Play::Matrix2D scaleMt = Play::Matrix2D(
		{ m_scaleX, 0.0f,0.0f },
		{ 0.0f, 1.0f,0.0f },
		{ m_pos.x,DISPLAY_HEIGHT - m_pos.y, 0.0f });
	Play::DrawSpriteTransformed(Play::GetSpriteId(spriteName), scaleMt * rotMt, 0);

	if(m_isRevealing)
	{
		m_animCounter += Timer::DeltaTime();

		if (m_animCounter > m_animLength)
		{
			m_isRevealing = false;
			m_animCounter = 0.0f;
		}
		m_revealAnim -= Timer::DeltaTime() * m_animSpeed;
		Play::DrawCircle(m_pos, m_revealAnim * 1.2f, Play::cGrey);
		Play::DrawCircle(m_pos, m_revealAnim * 0.8f, Play::cGrey);
		Play::DrawCircle(m_pos, m_revealAnim * 0.4f, Play::cGrey);
		Play::DrawCircle(m_pos, m_revealAnim * 0.2f, Play::cGrey);
	}

}
