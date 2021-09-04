#include "timer.h"

void Timer::start(float time)
{
	if (!stopped) stop();
	elapsedTime = 0.0f;
	limitTime = time;
	stopped = false;
}

void Timer::stop()
{
	stopped = true;
	elapsedTime = 0.0f;
}

bool Timer::isStopped()
{
	return stopped;
}

void Timer::update(float deltaTime)
{
	if (!stopped)
	{
		elapsedTime += deltaTime;
		if (elapsedTime > limitTime)
			stop();
	}
}
