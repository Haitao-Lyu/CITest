#pragma once
class Timer
{
private:

public:
	float m_timeCounter = 0;

	float m_timeInterval = 0;

	Timer() {};

	/*Set Interval*/
	Timer(float interval) : m_timeInterval(interval) {}

	void SetInterval(float interval);

	void SetInterval(int interval);

	/*Return true when meet time interval*/
	bool isReachTimeInterval();

	/*Restart the timer*/
	void Restart();

	/*Put in main update to set delta time*/
	static void UpdateDeltaTime(float elapsedTime);

	/*Get delta time*/
	static float DeltaTime();
};


