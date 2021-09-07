#include "entity.h"
#include "app.h"
#include "glm/gtx/vector_angle.hpp"

/*
Entity::Entity() : maxSpeed(0.1f)
{
	// set sprite origin to it's center
	auto spriteBounds = sprite.getLocalBounds();
	sprite.setOrigin(spriteBounds.width / 2.0f, spriteBounds.height / 2.0f);
}
*/

#define MAX_WALK_SPEED 80.0f

Entity::Entity() : Entity(nullptr, glm::vec2(0.0f))
{
}

Entity::Entity(Node* parent): Entity(parent, glm::vec2(0.0f))
{
	maxSpeed = MAX_WALK_SPEED;
}

Entity::Entity(const glm::vec2& position): Entity(nullptr, position)
{
	maxSpeed = MAX_WALK_SPEED;
}

Entity::Entity(Node* parent, const glm::vec2& position) : Node2D(parent, position), animationPlayer(this)
{
	maxSpeed = MAX_WALK_SPEED;
}

Entity::Entity(const std::string& texturePath): Node2D(), maxSpeed(MAX_WALK_SPEED), animationPlayer(this)
{
	animationPlayer.createAnimation("default", texturePath, 1, 1.0f);
	animationPlayer.play("default");
}

Entity::Entity(const Entity& other): Node2D(), maxSpeed(MAX_WALK_SPEED), animationPlayer(other.animationPlayer)
{
}

Entity::~Entity()
{
}

bool Entity::operator==(const Entity& other)
{
	return this == &other;
}

void Entity::rotate(glm::vec2 direction, float speed)
{
	speed = glm::clamp(speed, 0.0f, 1.0f);
	direction.y *= -1.0f;
	float angle = glm::angle(glm::normalize(direction), glm::vec2(0.0f, 1.0f));
	if (direction.x < 0.0f) angle *= -1.0f;
	float a = (chonky::lerpAngle(getRotation(), glm::degrees(angle), speed));
	setRotation(a);
}

void Entity::start()
{
	addChild(&animationPlayer);
}

void Entity::update(float delta)
{
}