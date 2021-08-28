#include "animationPlayer.h"
#include "app.h"
#include "debug.h"
#include <ranges>

AnimationPlayer::AnimationPlayer() : playTime(0.0f), playing(false), loop(true), currentAnimation(nullptr)
{
}

AnimationPlayer::~AnimationPlayer()
{
}

void AnimationPlayer::play(const std::string& animationName, bool looping)
{
	if (currentAnimation && currentAnimation->getName() == animationName) return;
	auto predicate = [&animationName](const Animation& animation) { return animationName == animation.getName(); };
	if (auto result = std::ranges::find_if(animations, predicate); result != animations.end())
	{
		stop();
		loop = looping;
		currentAnimation = &*result;
		playing = true;
	}
}

void AnimationPlayer::stop()
{
	playing = false;
	playTime = 0.0f;
}

void AnimationPlayer::draw(sf::RenderWindow* window)
{
	if (playing && currentAnimation || currentAnimation && currentAnimation->getHframes() == 1)
	{
		currentAnimation->setPosition(getPosition());
		currentAnimation->setRotation(getRotation());
		currentAnimation->setScale(getScale());
		currentAnimation->draw(window, playTime);
	}
}

void AnimationPlayer::start()
{
	if (currentAnimation)
	{
		stop();
		playing = true;
	}
}

void AnimationPlayer::update(float delta)
{
	if (currentAnimation->getHframes() > 1 && playing && currentAnimation)
	{
		playTime += delta;
		Debug::print("frame: " + std::to_string(currentAnimation->getFrame()));
		// if playTime is bigger than animation length, reset it. Stop if loop == false;
		if (playTime > currentAnimation->getFrameTime() * currentAnimation->getHframes()) 
		{
			playTime = 0.0f;
			if(!loop) stop();
		}
	}
}

void AnimationPlayer::createAnimation(std::string animationName, const std::string& texturePath, unsigned int hframes, float frameTime)
{
	Animation newAnimation(animationName, texturePath, hframes, frameTime);
	animations.push_back(newAnimation);
}

bool AnimationPlayer::isPlaying() const noexcept
{
	return playing;
}
