#pragma once
#include "Play.h"

enum class E_OBJTYPE
{
	E_NULL = -1,
	E_OILPLATFORM,
	E_OILCHUNK,
	E_Submarine,
	E_MXATYPENUM,
};

class GameObject 
{
public:
	static int total_id;
	int m_id = 0;
	E_OBJTYPE m_type = E_OBJTYPE::E_NULL;
	const char* spriteName = "";
	Play::Point2D m_pos{0.0f,0.0f};
	float m_rot = 0;
	float m_scale{ 1.0f };
	float m_spriteHeight = 0;
	float m_spriteWidth = 0;
public:
	GameObject(Play::Point2D pos, E_OBJTYPE m_type);

	GameObject(float x, float y, E_OBJTYPE m_type);

	//control logic
	virtual ~GameObject();
	virtual void Update() = 0;
	//control how to render
	virtual void Render();

	int GetID();

	virtual void SetPosition(Play::Point2D pos);

	virtual void SetPosition(float x,float y);

	virtual void Rotate(float rot);

	virtual void Rotate(int rot);

	virtual void SetScale(float scale);

	virtual void SetRotation(float rot);

	virtual void LookAt(GameObject* obj);

	virtual void LookAt(Play::Point2D pos);

	Play::Point2D& GetPosition();

	const char* GetSpriteName();

	void SetSpriteName(const char* name);

	//Draw ID Currnetly
	void DrawDebugInfo(Play::Colour color = Play::cRed);

};