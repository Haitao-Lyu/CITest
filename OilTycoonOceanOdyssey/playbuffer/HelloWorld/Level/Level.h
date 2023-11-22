#pragma once
#include <map>
#include <vector>
#include <string>
enum class E_BACKGROUND
{
	E_BLUE,
	E_GREEEN,
	E_PURPLE,
	E_RED,
	E_WOOD,
	E_YELLOW,
};

class SubMarine;

class Level
{
private:

	bool isStart = false;

	bool isEnd = false;

public:
	//level Logic arguments
	int m_id = -1;

	int m_maxCapacity = 30;
	float m_currenyStorage = 0;

	//Tools Amount
	int m_smallPlatform{0};
	int m_mediumPlatform{0};
	int m_LargePlatform{0};

	int m_detectionToool{ 0 };
	int m_RescuShip{ 0 };

	SubMarine* pSubmarin{ nullptr };


public:
	Level();

	~Level();

public:
	void OnEnter();

	void PlaceTheOilPlatform();
	void Update();

	void OnExit();

	/*Clear Non-Memory-Allocated-Relative Data*/
	void Clear();

	/*Destroy Memory-Allocated-Relative Data*/
	void Destroy();

	bool isLevelEnd();
};

