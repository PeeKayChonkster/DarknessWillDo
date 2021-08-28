#pragma once

class Runnable
{
protected:
	bool started = false;
public:
	Runnable();
	~Runnable();

	virtual void start() = 0;
	virtual void update(float delta) = 0;
};