#include "drawable.h"
#include "app.h"

Drawable::Drawable()
{
	App::registerDrawable(this);
}

Drawable::~Drawable()
{
	App::unregisterDrawable(this);
}