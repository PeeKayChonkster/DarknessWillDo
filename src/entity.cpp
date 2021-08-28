#include "entity.h"
#include "app.h"

/*
Entity::Entity() : maxSpeed(0.1f)
{
	// set sprite origin to it's center
	auto spriteBounds = sprite.getLocalBounds();
	sprite.setOrigin(spriteBounds.width / 2.0f, spriteBounds.height / 2.0f);
}
*/

Entity::Entity(const std::string& texturePath): Runnable(), maxSpeed(50.0f)
{
	animationPlayer.createAnimation("default", texturePath, 1, 1.0f);
	animationPlayer.play("default");
	start();
}

Entity::Entity(const Entity& other): Runnable(), maxSpeed(50.0f), animationPlayer(other.animationPlayer)
{
	start();
}

Entity::~Entity()
{
}

bool Entity::operator==(const Entity& other)
{
	return this == &other;
}

void Entity::start()
{
	if (started) return;
	started = true;
	addChild(&animationPlayer);
}

void Entity::update(float delta)
{
}