#pragma once
#include "GameObject.h"

enum class E_SubMarine
{
	SMALL,
	MEDIUM,
};

class SubMarine: public GameObject
{

	float m_revealDis = 30.f;
	float m_revealAnim = 0.f;
	float m_scaleX = 1;
	float m_animSpeed = 5.0f;

	float m_animCounter = 0.0f;
	float m_animLength = 2.0f;

	bool m_isRevealing = false;

public:
	E_SubMarine m_size = E_SubMarine::SMALL;
	SubMarine(Play::Point2D pos, E_SubMarine size = E_SubMarine::SMALL);

	~SubMarine();

	void SwitchType();
	void InputHandle();
	void OilDetection();
public:
	void Update() override;

	void Render() override;
};

