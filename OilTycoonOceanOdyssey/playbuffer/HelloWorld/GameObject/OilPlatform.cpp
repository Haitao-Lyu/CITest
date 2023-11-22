
#include "OilPlatform.h"
#include "UI/UIManager.h"
#include "GameObjectMgr.h"
#include "GameTool/Timer.h"
#include "OilChunk.h"

OilPlatform::OilPlatform(Play::Point2D pos, E_OilPlatformSize size): GameObject(pos, E_OBJTYPE::E_OILPLATFORM)
{
	m_size = size;
	switch (m_size)
	{
	case E_OilPlatformSize::SMALL:
		spriteName = "smallRig";
		m_MaxCapacity = 10.0f;
		break;
	case E_OilPlatformSize::MEDIUM:
		spriteName = "mediumRig";
		m_MaxCapacity = 20.f;
		break;
	case E_OilPlatformSize::LARGE:
		spriteName = "largeRig";
		m_MaxCapacity = 30.0f;
		break;
	default:
		break;
	}

}

OilPlatform::~OilPlatform()
{

}

void OilPlatform::DrillDown()
{
	using namespace Play;
	if (!m_isDrilling)
	{
		if (!m_isSucking)
		{
			drillHeadPos = m_pos;
			suckUpPos = m_pos;
		}
		Play::DrawRect(Play::Vector2f{ m_pos.x , drillHeadPos.y }, Play::Vector2f{ drillHeadPos.x + pipeThickness , m_pos.y  }, Play::cGrey, true);//#temp draw rect
		return;
	}

	m_drillDistance += m_drillSpeed * Timer::DeltaTime();  
	drillHeadPos = Play::Vector2f{ m_pos.x, m_pos.y + m_drillDistance };
	endSuckUpPos = drillHeadPos;
	suckUpPos = drillHeadPos;
	Play::DrawRect(Play::Vector2f{ m_pos.x , drillHeadPos.y  }, Play::Vector2f{ drillHeadPos.x + pipeThickness , m_pos.y }, Play::cGrey, true);//#temp draw rect
	//Play::DrawLine(m_pos, drillHeadPos, Play::cGrey);
}

void OilPlatform::SuckUp()
{

	if (!m_isSucking)
		return;

	m_suckUpDistance += m_suckSpeed * Timer::DeltaTime();
	if(!m_isSuckEnd)
	suckUpPos = Play::Vector2f{ m_pos.x, drillHeadPos.y - m_suckUpDistance};

	float distance = Play::length(suckUpPos - m_pos);
	if (distance <= 2.0f)
	{
		suckUpPos = m_pos;
		m_isSuckEnd = true;
	}
	Play::DrawRect(Play::Vector2f{ drillHeadPos.x , drillHeadPos.y }, Play::Vector2f{ suckUpPos.x + pipeThickness , suckUpPos.y }, Play::cBlack, true);//#temp draw rect

	if (m_isChunkEmpty)
	{
		m_endUpDistance += m_suckSpeed * Timer::DeltaTime();
		if (!m_isEndSuckEnd)
			endSuckUpPos = Play::Vector2f{ m_pos.x, drillHeadPos.y - m_endUpDistance };

		float distance2 = Play::length(endSuckUpPos - m_pos);
		if (distance2 <= 2.0f)
		{
			endSuckUpPos = m_pos;
			m_isEndSuckEnd = true;
		}
		Play::DrawRect(Play::Vector2f{ drillHeadPos.x , drillHeadPos.y }, Play::Vector2f{ endSuckUpPos.x + pipeThickness , endSuckUpPos.y }, Play::cGrey, true);//#temp draw rect
	}
}


void OilPlatform::Update()
{
	static float clipDis = 10.0f;
	DrillDown();
	SuckUp();
	Render();

	if (m_capacity <= m_MaxCapacity)
	{
		int EmptyCounter[2]{ -1, -1 };
		std::vector<GameObject*>& objs = GameObjectMgr::GetGameObjectsByType(E_OBJTYPE::E_OILCHUNK);

		for (GameObject* obj : objs)
		{
			float distance = Play::length(obj->m_pos - drillHeadPos);
			if (distance <= clipDis)
			{
				m_isDrilling = false;
				m_isSucking = true;
				OilChunk* pChunk = reinterpret_cast<OilChunk*>(obj);

				pChunk->isRevealed = true;
				if (pChunk->isEmpty)
				{
					EmptyCounter[0]++;
				}
				else
				{
					EmptyCounter[1] = 1;
					pChunk->BeSucked(m_isSuckEnd, this);
				}
			}
		}

		if (EmptyCounter[1] == 1 && !m_isDrilling)
		{
			m_isChunkEmpty = false;
		}
		else
		{
			m_isChunkEmpty = true;
		}
	}
	else
	{
		m_isChunkEmpty = true;
	}
}

void OilPlatform::Render()
{
	Play::DrawSprite(Play::GetSpriteId(spriteName), m_pos, 0);
}
