#include "Play.h"
#include "GameObject/OilPlatform.h"
#include "GameObjectMgr.h"
#include <map> // map faster or vector faster ? ? ?
#include "GameTool/DebugTool.h"
#include "GameObject/OilChunk.h"
#include "GameObject/SubMarine.h"

namespace GameObjectMgr
{
	//sacrifice more memory for searching speed, or reduce speed for more memory ? 
	std::map<int, GameObject*> g_gameObjectMapAll;

	std::map<int, std::vector<GameObject*>> g_gameObjectMapbyType;

	std::map<int, GameObject*> g_gameObjectForDelete;

	void AddNewGameObject(GameObject& obj)
	{
		g_gameObjectMapAll[obj.m_id] = &obj;
		g_gameObjectMapbyType[static_cast<int>(obj.m_type)].push_back(&obj);
	}

	void RemoveGameObject(GameObject& obj)
	{
		if (g_gameObjectMapAll.find(obj.m_id) != g_gameObjectMapAll.end())
		{
			g_gameObjectMapAll.erase(obj.m_id);
			
			for (int i = 0; i < g_gameObjectMapbyType[static_cast<int>(obj.m_type)].size(); i++)
			{
				GameObject* temp = g_gameObjectMapbyType[static_cast<int>(obj.m_type)][i];
				if(temp)
				if (temp->m_id == obj.m_id)
				{
					//move to delete list
					g_gameObjectForDelete.insert({ temp->m_id, temp });
					//erase from objects map
					g_gameObjectMapbyType[static_cast<int>(obj.m_type)].erase(g_gameObjectMapbyType[static_cast<int>(obj.m_type)].begin() + i--);
				}
			}
		}

	}

	void RemoveGameObjectByid(int id)
	{
		GameObject& obj = *GetGameObjectByid(id);
		if (g_gameObjectMapAll.find(id) != g_gameObjectMapAll.end())
		{
			g_gameObjectMapAll.erase(id);
			for (int i = 0; i < g_gameObjectMapbyType[static_cast<int>(obj.m_type)].size(); i++)
			{
				GameObject* temp = g_gameObjectMapbyType[static_cast<int>(obj.m_type)][i];
				if (temp->m_id == obj.m_id)
				{
					//move to delete list
					g_gameObjectForDelete.insert({ temp->m_id, temp });
					g_gameObjectMapbyType[static_cast<int>(obj.m_type)].erase(g_gameObjectMapbyType[static_cast<int>(obj.m_type)].begin() + i--);
				}
			}
		}
		
	}

	void UpdateGameObjectsByType(E_OBJTYPE type)
	{
		//check how many game objects are there
		//DebugValue((int)g_gameObjectMapbyType.size());
		if (g_gameObjectMapbyType.find(static_cast<int>(type)) != g_gameObjectMapbyType.end())
		{
			//Debug
			//std::vector<GameObject*> &list = g_gameObjectMapbyType[static_cast<int>(type)];
			//DebugValue((int)list.size());
			for (GameObject* obj: g_gameObjectMapbyType[static_cast<int>(type)])
			{
				if(obj)
				obj->Update();
			}
		}
	}

	void ClearAllGameobjects()
	{
		//delete all pointer in global list
		for (auto& [id, obj] : g_gameObjectMapAll)
		{
			delete obj;
		}

		//Two map have the same instance, so pointer point to the same object ?
		for (auto& [id, list] : g_gameObjectMapbyType)
		{
			list.clear();
		}
		//pointer is all clean, so just clear 
		g_gameObjectMapAll.clear();
		g_gameObjectMapbyType.clear();// will this clear the vector inside map as well?
	}

	void HandleGameObjectsDestroy()
	{
		//check how many game objects are there
		if (!g_gameObjectForDelete.empty())
		{
			for (auto& [id, obj] : g_gameObjectForDelete)
			{
				g_gameObjectMapAll.erase(id);
				delete obj;
			}
			g_gameObjectForDelete.clear();
		}
	}

	OilPlatform* MakeOilPlatform(Play::Point2f pos, E_OilPlatformSize size)
	{
		return new OilPlatform(pos, size);
	}

	OilChunk* MakeOilChunk(Play::Point2f pos, E_OilChunk size)
	{
		return new OilChunk(pos, size);
	}

	SubMarine* MakeSubMarine(Play::Point2f pos, E_SubMarine size)
	{
		return new SubMarine(pos, size);;
	}

	GameObject* GetGameObjectByid(int id)
	{
		if (g_gameObjectMapAll.find(id) != g_gameObjectMapAll.end())
			return g_gameObjectMapAll[id];
		return nullptr;
	}

	std::vector<GameObject*>& GetGameObjectsByType(E_OBJTYPE type)
	{
		if (g_gameObjectMapbyType.find(static_cast<int>(type)) != g_gameObjectMapbyType.end())
			return g_gameObjectMapbyType[static_cast<int>(type)];
		else
			return g_gameObjectMapbyType[static_cast<int>(type)];
	}


}

