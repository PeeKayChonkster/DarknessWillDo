#include "player.h"
#include "glm/common.hpp"
#include "glm/gtx/vector_angle.hpp"
#include "debug.h"
#include "glm/gtc/quaternion.hpp"
#include "app.h"
#include "bullet.h"

const std::string Player::type = "Player";

Player::Player()
{
}

Player::Player(const std::string& texturePath) : Entity(texturePath)
{
}

Player::Player(const glm::vec2& position) : Entity(position)
{
}

Player::~Player()
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
	if (Mouse::isButtonPressed(Mouse::Right) && App::getWindow()->hasFocus())
	{
		// get global mouse coordinates
		auto mousePosition = App::getWindow()->mapPixelToCoords(Mouse::getPosition(*App::getWindow()));
		
		moveTarget = glm::vec2(float(mousePosition.x), float(mousePosition.y));
	}
	if (Mouse::isButtonPressed(Mouse::Left) && App::getWindow()->hasFocus())
	{
	}
	/////////////////////

	//// Window Events ////
	for (auto& e : windowEvents)
	{
		if (e.type == sf::Event::MouseButtonPressed)
		{
			if (e.mouseButton.button == Mouse::Left)
			{
				shoot(glm::vec2(e.mouseButton.x, e.mouseButton.y));
			}
		}
	}
	windowEvents.clear();
	///////////////////////

	//velocity = chonky::clampVec(velocity, 0.0f, maxSpeed) * delta;
	float distance = glm::distance(moveTarget, getPosition());

	// if there is distance to walk
	if (distance > 3.0f)
	{
		velocity = glm::normalize(moveTarget - getPosition()) * maxSpeed * delta;
		// move according to input
		move(velocity);

		animationPlayer.play("walk");

		Debug::print("MoveTarget: " + std::to_string(moveTarget.x) + "||" + std::to_string(moveTarget.y));
		Debug::print("Distance: " + std::to_string(distance));

		// TEMP
		// play step sound every 4th frame
		static bool played = false;
		Debug::print("SoundSources: " + std::to_string(audioPlayer.getNumberOfSoundSources()));
		if (animationPlayer.getCurrentAnimation()->getFrame() % 5 == 0 && animationPlayer.getCurrentAnimation()->getFrame() != 0 && !played)
		{
			audioPlayer.playSound("step", true);
			played = true;
		}
		else if (animationPlayer.getCurrentAnimation()->getFrame() % 5 != 0)
		{
			played = false;
		}
			


		// rotate in the direction of velocity
		rotate(velocity, 0.3f);
	}
	else
	{
		animationPlayer.play("idle");
	}
}

void Player::pushEvent(sf::Event event)
{
	windowEvents.push_back(event);
}

// TODO: this function won't work because of the lifespan of bullet object
void Player::shoot(glm::vec2 point)
{
	if (timer.isStopped())
	{
		Bullet* bullet = new Bullet;
		bullet->setPosition(getPosition());
		App::addToRoot(bullet);
		auto direction = point - getPosition();
		bullet->fire(direction);
		// get global mouse coordinates
		auto mousePosition = App::getWindow()->mapPixelToCoords(sf::Mouse::getPosition(*App::getWindow()));
		moveTarget = getPosition();
		rotate(chonky::sf_to_glm_vec(mousePosition) - getPosition(), 1.0f);
		animationPlayer.play("shoot", false, false);
		audioPlayer.playSound("shot", true);
		bullets.push_back(bullet);
		timer.start(0.28f);
	}
}

void Player::start()
{
	Entity::start();
	moveTarget = getPosition();
	setScale(glm::vec2(1.5f));

	addChild(&timer);

	//animationPlayer.createAnimation("idle", App::TEXTURES_PATH + "human_idle.png", 1, 0.15f);
	//animationPlayer.createAnimation("walk", App::TEXTURES_PATH + "human_walk_sheet.png", 8, 0.15f);
	animationPlayer.createAnimation("idle", App::TEXTURES_PATH + "leonard_idle_sheet.png", 40, 0.1f);
	animationPlayer.createAnimation("walk", App::TEXTURES_PATH + "leonard_walk_sheet.png", 11, 0.1f);
	animationPlayer.createAnimation("shoot", App::TEXTURES_PATH + "leonard_shoot_sheet.png", 4, 0.07f);
	animationPlayer.play("idle");

	audioPlayer.loadSound("step", App::SOUND_PATH + "Step.wav", 70.0f);
	audioPlayer.loadSound("hit1", App::SOUND_PATH + "Hit1.wav", 50.0f);
	audioPlayer.loadSound("shot", App::SOUND_PATH + "Shot.wav", 30.0f);
}

void Player::update(float delta)
{
	getInput(delta);
}
