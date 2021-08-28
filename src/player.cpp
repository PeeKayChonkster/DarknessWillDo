#include "player.h"
#include "glm/common.hpp"
#include "glm/gtx/vector_angle.hpp"
#include "debug.h"
#include "glm/gtc/quaternion.hpp"

Player::Player(const std::string& texturePath) : Entity(texturePath)
{
	start();
}

void Player::getInput(float delta)
{
	using sf::Keyboard;
	using sf::Mouse;

	glm::vec2 velocity(0.0f);
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		velocity += glm::vec2(0.0f, -maxSpeed);
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		velocity += glm::vec2(0.0f, maxSpeed);
	}
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		velocity += glm::vec2(-maxSpeed, 0.0f);
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		velocity += glm::vec2(maxSpeed, 0.0f);
	}

	velocity = chonky::clampVec(velocity, 0.0f, maxSpeed) * delta;

	// if there was input
	if (glm::length(velocity) > 0.0f)
	{
		// move according to input
		move(velocity);

		// rotate in the direction of velocity
		velocity.y *= -1.0f;
		float angle = glm::angle(glm::normalize(velocity), glm::vec2(0.0f, 1.0f));
		Debug::print("Angle: " + std::to_string(glm::degrees(angle)));
		if (velocity.x < 0.0f) angle *= -1.0f;
		float rotation = getRotation();
		Debug::print("Player rotation: " + std::to_string(rotation));
		float a = (chonky::lerpAngle(rotation, glm::degrees(angle), 0.3f));
		setRotation(a);
	}
}

void Player::start()
{
	if (started) return;
	started = true;
	Entity::start();
}

void Player::update(float delta)
{
	getInput(delta);
}
