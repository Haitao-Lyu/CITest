#pragma once
#include "GameObject.h"
enum class E_OilPlatformSize
{
	SMALL,
	MEDIUM,
	LARGE,
};

class OilPlatform: public GameObject
{
public:
	E_OilPlatformSize m_size = E_OilPlatformSize::SMALL;

	Play::Vector2f drillHeadPos{ 0.0f, 0.0f };
	Play::Vector2f suckUpPos{ 0.0f, 0.0f };
	Play::Vector2f endSuckUpPos{ 0.0f, 0.0f };

	float m_capacity = 0.0f;
	float m_MaxCapacity = 0.0f;

	float pipeThickness = 4.0f;

	float m_drillDistance = 0;
	float m_suckUpDistance = 0;
	float m_endUpDistance = 0;

	float m_drillSpeed = 10.0f;
	float m_suckSpeed = 5.f;

	bool m_isDrilling = false;

	bool m_isSucking = false;
	bool m_isSuckEnd = false;

	bool m_isEndSuckEnd = false;
	bool m_isChunkEmpty = false;

public:
	OilPlatform(Play::Point2D pos, E_OilPlatformSize size = E_OilPlatformSize::SMALL);

	~OilPlatform();

public:
	void Update() override;

	void Render() override;

	inline void SetSize(E_OilPlatformSize size) { m_size = size; };

	void DrillDown();
	void SuckUp();

};

