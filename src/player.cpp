#include "player.h"
#include "glm/common.hpp"
#include "glm/gtx/vector_angle.hpp"
#include "debug.h"
#include "glm/gtc/quaternion.hpp"
#include "app.h"

Player::Player()
{
}

Player::Player(const std::string& texturePath) : Entity(texturePath)
{
}

void Player::getInput(float delta)
{
	using sf::Keyboard;
	using sf::Mouse;

	glm::vec2 velocity(0.0f);

	//// Keyboard Input ////
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
	////////////////////////

	//// Mouse Input ////
	if (Mouse::isButtonPressed(Mouse::Left) && App::getWindow()->hasFocus())
	{
		// get global mouse coordinates
		auto mousePosition = App::getWindow()->mapPixelToCoords(Mouse::getPosition(*App::getWindow()));
		
		moveTarget = glm::vec2(float(mousePosition.x), float(mousePosition.y));
	}
	/////////////////////

	//velocity = chonky::clampVec(velocity, 0.0f, maxSpeed) * delta;
	float distance = glm::distance(moveTarget, getPosition());

	// if there is distance to walk
	if (distance > 0.5f)
	{
		velocity = glm::normalize(moveTarget - getPosition()) * maxSpeed * delta;
		// move according to input
		move(velocity);

		animationPlayer.play("walk");


		// play step sound every 4th frame
		static bool played = false;
		Debug::print("SoundSources: " + std::to_string(audioPlayer.getNumberOfSoundSources()));
		if (animationPlayer.getCurrentAnimation()->getFrame() % 4 == 0 && !played)
		{
			audioPlayer.playSound("step", true);
			played = true;
		}
		else if (animationPlayer.getCurrentAnimation()->getFrame() % 4 != 0)
		{
			played = false;
		}
			

		// rotate in the direction of velocity
		velocity.y *= -1.0f;
		float angle = glm::angle(glm::normalize(velocity), glm::vec2(0.0f, 1.0f));
		if (velocity.x < 0.0f) angle *= -1.0f;
		Debug::print("MoveTarget: " + std::to_string(moveTarget.x) + "||" + std::to_string(moveTarget.y));
		Debug::print("Distance: " + std::to_string(distance));
		float a = (chonky::lerpAngle(getRotation(), glm::degrees(angle), 0.3f));
		setRotation(a);
	}
	else
	{
		animationPlayer.play("idle");
	}
}

void Player::start()
{
	Entity::start();
	moveTarget = getPosition();

	animationPlayer.createAnimation("idle", App::TEXTURES_PATH + "human_idle.png", 1, 0.15f);
	animationPlayer.createAnimation("walk", App::TEXTURES_PATH + "human_walk_sheet.png", 8, 0.15f);
	animationPlayer.play("idle");

	audioPlayer.loadSound("step", App::SOUND_PATH + "Step.wav", 70.0f);
	audioPlayer.loadSound("Hit1", App::SOUND_PATH + "Hit1.wav", 50.0f);
}

void Player::update(float delta)
{
	getInput(delta);
}
