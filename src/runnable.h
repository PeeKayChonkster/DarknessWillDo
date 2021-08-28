#pragma once

class Runnable
{
public:
	Runnable();
	~Runnable();

	virtual void start() = 0;
	virtual void update(float delta) = 0;
};