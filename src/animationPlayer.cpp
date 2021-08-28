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
	auto predicate = [&animationName](const Animation& animation) { return animationName == animation.getName(); };
	if (auto result = std::ranges::find_if(animations, predicate); result != animations.end())
	{
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
		Debug::print("AnimPlayer rotation: " + std::to_string(getRotation()));
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
	animations.emplace_back(animationName, texturePath, hframes, frameTime);
}

bool AnimationPlayer::isPlaying() const noexcept
{
	return playing;
}
