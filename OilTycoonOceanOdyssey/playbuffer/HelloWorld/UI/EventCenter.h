#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <string.h>

template<typename ...Args>
class Signal
{
public:
	using VariadicFunc = std::function<void(Args...)>;
	void emit(Args... args)
	{
		for (VariadicFunc& observer : m_observers)
		{
			//all observer will do the function passed in with same amounts arguments
			observer(std::forward<Args>(args)...);//forward turn lvalue into rvalue
		}
	}
	void connect(VariadicFunc func)
	{
		m_observers.push_back(func);
	}
private:
	std::vector<VariadicFunc> m_observers;
};


class Event 
{
	typedef std::function<void()> FunctionType;
private:
	std::vector<FunctionType> m_functions;//list of function?

public:
	Event();

	Event(FunctionType function);

	void add(FunctionType function);

	void operator() () const;//overload brackets
};

class EventListener 
{
	typedef std::function<void()> FunctionType;
private:
	const char* specialName = "";//Unique name

	Event m_event;
public:
	EventListener();

	EventListener(const char* name);

	bool operator == (const EventListener& listener) const;

	void addEvent(FunctionType function);

	virtual void onEvent(const Event* event);

	virtual void onEvent();
};

namespace EventCenter
{
	void RegisterListener(const char* eventName, EventListener &listener);

	void UnregisterListener(const char* eventName, EventListener &listener);

	void UnregisterListenersByEvent(const char* eventName);

	void PostEvent(const char* eventName, const Event& event);

	void PostEvent(const char* eventName);

	void DebugEvent();
	
	void Clear();
}


