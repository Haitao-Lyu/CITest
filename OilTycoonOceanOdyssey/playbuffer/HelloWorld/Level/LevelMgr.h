#pragma once
#include "../Level/level.h"


class LevelMgr
{
private:
	std::vector<Level> level_list;

	int maxLevelNumber = 0;

	int currentLevelIndex = 0;

	Level* currentLevel = nullptr;

	static LevelMgr* _instance;




private:

	LevelMgr();

	LevelMgr(const LevelMgr &levelMgr) = delete;

	const LevelMgr& operator==(const LevelMgr& levelMgr) = delete;

public:

	static LevelMgr* GetInstance();

	int GetMaxLevelNumber();

	void AddNewLevel(Level& level);

	void SetCurrentLevel(int index);

	Level* GetCurrentLevel();

	void ClearAllLevel();

	void ClearCurrentLevel();

	Level* GetLevel(int i);

	void Update();

	void Destroy();
};

