#include "EventCenter.h"


namespace EventCenter
{
	static std::map<const char*, std::vector<EventListener>> g_listeners_;

	void RegisterListener(const char* eventName, EventListener &listener)
	{
		//DebugValue((int)g_listeners_.size());
		if (!g_listeners_[eventName].empty())
		{
			for (int i = 0; i < g_listeners_[eventName].size(); i++)
			{
				if (g_listeners_[eventName][i] == listener)
				{
					return;
				}
			}
			g_listeners_[eventName].push_back(listener);
			return;
		}
		g_listeners_[eventName].push_back(listener);
	}

	void UnregisterListener(const char* eventName, EventListener &listener)
	{
		if (g_listeners_.empty())
			return;
		//DebugValue(static_cast<int>(g_listeners_[eventName].size()),"listener:",20);
		//how to distinguish listener?
	}

	void UnregisterListenersByEvent(const char* eventName)
	{
		g_listeners_.erase(eventName);
	}

	void PostEvent(const char* eventName,const Event& event) 
	{
		if (g_listeners_.empty())
			return;
		//DebugValue(static_cast<int>(g_listeners_[eventName].size()),"listener:",20);
		for (auto& listener : g_listeners_[eventName])
		{
			listener.onEvent(&event);
		}
	}

	void PostEvent(const char* eventName)
	{
		if (g_listeners_.empty())
			return;
		//DebugValue(static_cast<int>(g_listeners_[eventName].size()),"listener:",20);
		for (auto& listener : g_listeners_[eventName])
		{
			listener.onEvent();
		}
	}

	void DebugEvent()
	{

	}
	void ClearAll()
	{
		for (auto& [name, list] : g_listeners_)
		{
			list.clear();
		}
		g_listeners_.clear();
	}
}


Event::Event()
{
}

Event::Event(FunctionType function)
{
	add(function);
}

void Event::add(FunctionType function)
{
	m_functions.push_back(function);
}

void Event::operator()() const
{
	for (auto& f : m_functions)
	{
		f();
	}
}

EventListener::EventListener()
{
}

EventListener::EventListener(const char* name)
{
	specialName = name;
}

bool EventListener::operator==(const EventListener& listener) const
{
	if (std::strcmp(specialName,listener.specialName))
		return true;
	return false;
}

void EventListener::addEvent(FunctionType function)
{
	m_event.add(function);
}

void EventListener::onEvent(const Event* event)
{
	m_event.add(*event);
	(m_event)();
}

void EventListener::onEvent()
{
	(m_event)();
}

