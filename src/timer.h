#pragma once
#include "node.h"

class Timer : public Node
{
private:
	float elapsedTime;
	float limitTime;
	bool stopped;
public:
	void start(float time);
	void stop();
	bool isStopped();
	virtual void update(float deltaTime) override;
};

