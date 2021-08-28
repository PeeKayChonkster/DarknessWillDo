#include "runnable.h"
#include "app.h"

Runnable::Runnable()
{
	App::registerRunnable(this);
}

Runnable::~Runnable()
{
	App::unregisterRunnable(this);
}