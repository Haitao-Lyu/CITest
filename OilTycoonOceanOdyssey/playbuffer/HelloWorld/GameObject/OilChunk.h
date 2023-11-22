#pragma once
#include "GameObject.h"
enum class E_OilChunk
{
	SMALL,
	MEDIUM,
	LARGE,
};

class OilPlatform;

class OilChunk:public GameObject
{
	E_OilChunk m_size = E_OilChunk::SMALL;

public:
	OilChunk(Play::Point2D pos, E_OilChunk size = E_OilChunk::SMALL);

	~OilChunk();

	float m_OilNum = 0;
	float m_OriginOilNum = 0;
	
	float m_drainedSpeed = 0.8f;

	bool isEmpty{false};
	bool isRevealed{false};
public:
	void Update() override;

	void Render() override;
	
	void BeSucked(bool isiSuckReachTop, OilPlatform* Pplatform);

	inline void SetSize(E_OilChunk size) { m_size = size; };
};