#include "bullet.h"
#include "app.h"
#include "debug.h"

const std::string Bullet::type = "Bullet";

Bullet::Bullet()
{
}

Bullet::Bullet(Node* parent, const glm::vec2& position) : Entity(parent, position)
{
}

Bullet::~Bullet()
{
	//Debug::printPersistent(type + " deconstruction");
}

void Bullet::fire(glm::vec2 direction)
{
	if (!fired)
	{
		initialPosition = getPosition();
		this->direction = glm::normalize(direction);
		fired = true;
		animationPlayer.play("bullet");
		rotate(direction, 1.0f);
	}
	else
		return;
}

void Bullet::start()
{
	Entity::start();
	animationPlayer.createAnimation("bullet", App::TEXTURES_PATH + "bullet.png", 1, 0.1);
	setScale(glm::vec2(0.1f));
}

void Bullet::update(float delta)
{
	if (fired)
	{
		move(direction * speed * delta);
		//Debug::print("Bullet: " + std::to_string(getPosition().x) + "|" + std::to_string(getPosition().y));
		if (float result = glm::distance(initialPosition, getPosition()); result > maxDistance)
		{
			fired = false;
			App::registerForDeletion(this);
		}
	}
	else
		return;
}
