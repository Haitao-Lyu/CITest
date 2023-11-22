#include "LevelMgr.h"


LevelMgr* LevelMgr::_instance;




LevelMgr::LevelMgr()
{

}

LevelMgr* LevelMgr::GetInstance()
{
	if (_instance)
	{
		return _instance;
	}
	return _instance = new LevelMgr();
}


int LevelMgr::GetMaxLevelNumber()
{
	return maxLevelNumber;
}

void LevelMgr::Destroy()
{
	if (_instance)
		delete _instance;
}

void LevelMgr::ClearCurrentLevel()
{
	if (currentLevel)
	{
		currentLevel->Destroy();
		currentLevel = nullptr;
		currentLevelIndex = 0;
	}
}

Level* LevelMgr::GetLevel(int i)
{
	if(i < level_list.size())
		return &level_list[i];
	return nullptr;
}

void LevelMgr::Update()
{
	if(currentLevel)
		currentLevel->Update();

	Level* newLevel = nullptr;
	if (currentLevel)
	{
		if (currentLevel->isLevelEnd())
		{
			newLevel = &level_list[currentLevelIndex++];
		}
	}
	else
	{
		// ? ? ? ? ? ? ? 
		//Get The pointer of the vector , when delete one, all the element in list is deleted
		//currentLevel = &level_list[currentLevelIndex++]; 
		// -> Pointer Won't change, But item in list will shift for any reason -> cause runtime bug
		// ? ? ? ? ? ? ? ? 
		//Enter First Level
		currentLevel = &level_list[currentLevelIndex++];
		currentLevel->OnEnter();
	}

	//Check If Level has Changed,call enter and exit function
	if (newLevel != nullptr)
	{
		currentLevel->OnExit();
		currentLevel = newLevel;
		currentLevel->OnEnter();
	}
}

void LevelMgr::ClearAllLevel()
{
	//Call destructor for each level
	level_list.clear();
	//Reset current level index
	currentLevel = nullptr;
	currentLevelIndex = 0;
	maxLevelNumber = 0;
}

void LevelMgr::AddNewLevel(Level& level)
{
	level_list.push_back(level);
	level_list.back().m_id = static_cast<int>(level_list.size() - 1);
	maxLevelNumber++;
}

void LevelMgr::SetCurrentLevel(int index)
{
	if (currentLevel != nullptr)
	{
		currentLevel->OnExit();
		currentLevel = &level_list[index];
		currentLevelIndex = index + 1;
		currentLevel->OnEnter();
	}
	else
	{
		currentLevel = &level_list[index];
		currentLevel->OnEnter();
		currentLevelIndex = index + 1;
	}
}

Level* LevelMgr::GetCurrentLevel()
{
	return currentLevel;
}
