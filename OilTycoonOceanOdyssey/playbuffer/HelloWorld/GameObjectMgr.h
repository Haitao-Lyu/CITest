#pragma once
#include "GameObject.h"

class OilPlatform;
class OilChunk;
class SubMarine;

enum class E_OilPlatformSize;
enum class E_OilChunk;
enum class E_SubMarine;

namespace GameObjectMgr
{
	void AddNewGameObject(GameObject& obj);

	void RemoveGameObject(GameObject& obj);

	void RemoveGameObjectByid(int id);

	void UpdateGameObjectsByType(E_OBJTYPE TYPE);

	void ClearAllGameobjects();

	void HandleGameObjectsDestroy();

	OilPlatform* MakeOilPlatform(Play::Point2f pos, E_OilPlatformSize size);
	OilChunk* MakeOilChunk(Play::Point2f pos, E_OilChunk size);
	SubMarine* MakeSubMarine(Play::Point2f pos, E_SubMarine size);

	GameObject* GetGameObjectByid(int id);

	std::vector<GameObject*>& GetGameObjectsByType(E_OBJTYPE type);
}

