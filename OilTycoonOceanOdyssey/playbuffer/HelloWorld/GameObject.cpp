#include "Play.h"
#include "GameObject.h"
#include "UI/UIManager.h"
#include "GameTool/DebugTool.h"
#include "GameObjectMgr.h"
int GameObject::total_id = 0;

GameObject::GameObject(Play::Point2D pos, E_OBJTYPE type)
{
	m_pos = pos;
	m_type = type;
	m_id = total_id;
	total_id++;
	GameObjectMgr::AddNewGameObject(*this);
}

GameObject::GameObject(float x, float y, E_OBJTYPE type)
{
	m_pos.x = x;
	m_pos.y = y;
	m_type = type;
	m_id = total_id;
	total_id++;
	GameObjectMgr::AddNewGameObject(*this);
}

GameObject::~GameObject()
{
}


int GameObject::GetID()
{
	return m_id;
}

void GameObject::SetPosition(Play::Point2D pos)
{
	m_pos = pos;
}

void GameObject::SetPosition(float x, float y)
{
	m_pos = { x,y };
}

void GameObject::Rotate(float rot)
{
	while (rot < 0)
	{
		rot += 360;
	}
	while (rot >= 360)
	{
		rot -= 360;
	}

	m_rot += rot;

	if (m_rot >= 360)
	{
		m_rot -= 360;
	}
	if (m_rot < 0)
	{
		m_rot += 360;
	}

}

void GameObject::Rotate(int rot)
{
	float rot_f = static_cast<float>(rot);
	while (rot_f < 0)
	{
		rot_f += 360;
	}
	while (rot_f > 360)
	{
		rot_f -= 360;
	}
	m_rot = rot_f;
}

void GameObject::SetScale(float scale)
{
	m_scale = scale;
}

void GameObject::SetRotation(float rot)
{
	while (rot < 0)
	{
		rot += 360;
	}
	while (rot > 360)
	{
		rot -= 360;
	}
	m_rot = rot;
}

void GameObject::LookAt(GameObject* obj)
{
	//on top
	if (obj->m_pos.y < this->m_pos.y)
	{
		m_rot = 0;
	}
	else if (obj->m_pos.x < this->m_pos.x)
	{
		m_rot = 90;
	}
	else if (obj->m_pos.y > this->m_pos.y)
	{
		m_rot = 180;
	}
	else if (obj->m_pos.x > this->m_pos.x)
	{
		m_rot = 270;
	}
}

void GameObject::LookAt(Play::Point2D pos)
{
	//on top
	if (pos.y < this->m_pos.y)
	{
		m_rot = 0;
	}
	else if (pos.x < this->m_pos.x)
	{
		m_rot = 90;
	}
	else if (pos.y > this->m_pos.y)
	{
		m_rot = 180;
	}
	else if (pos.x > this->m_pos.x)
	{
		m_rot = 270;
	}
}

Play::Point2D& GameObject::GetPosition()
{
	return m_pos;
}

const char* GameObject::GetSpriteName()
{
	return spriteName;
}

void GameObject::SetSpriteName(const char* name)
{
	spriteName = name;
}

void GameObject::DrawDebugInfo(Play::Colour color)
{
	Play::DrawDebugText(m_pos, std::to_string(m_id).c_str(), color, true);
}

void GameObject::Render()
{
	Play::DrawSprite(Play::GetSpriteId(spriteName), m_pos, 0);
}

