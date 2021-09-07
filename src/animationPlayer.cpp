#include "animationPlayer.h"
#include "app.h"
#include "debug.h"
#include <ranges>
#include "SFML/Audio.hpp"
#include "node2D.h"

const std::string AnimationPlayer::type = "Animation Player";

AnimationPlayer::AnimationPlayer(const Node2D* target) : target(target), playTime(0.0f), playing(false), loop(true), allowedToInterrupt(true),currentAnimation(nullptr)
{
}

AnimationPlayer::~AnimationPlayer()
{
}

void AnimationPlayer::play(const std::string& animationName, bool looping, bool interruptable)
{
	if (currentAnimation && currentAnimation->getName() == animationName)
	{
		if (playing) return;
		else playing = true;
	}
	else
	{
		if (playing && !allowedToInterrupt) return;
		allowedToInterrupt = interruptable;
		auto predicate = [&animationName](const Animation& animation) { return animationName == animation.getName(); };
		if (auto result = std::ranges::find_if(animations, predicate); result != animations.end())
		{
			if(playing) stop();
			loop = looping;
			currentAnimation = &*result;
			playing = true;
		}
		else
		{
			Debug::printPersistent("Didn't find animation to play. Name: " + animationName);
		}
	}
}


// TODO: this function stops drawing entirely, which is bad. Flickering occurs between animations.
// This all happens because of wrong update order. Children should update before parents
void AnimationPlayer::stop()
{
	playTime = 0.0f;
	currentAnimation = nullptr;
	playing = false;
}

void AnimationPlayer::draw(sf::RenderTarget* window)
{
	if ((playing && currentAnimation) || (currentAnimation && currentAnimation->getHframes() == 1))
	{
		unsigned int a = currentAnimation->getHframes(); // TEMP
		currentAnimation->setPosition(target->getGlobalPosition());
		currentAnimation->setRotation(target->getGlobalRotation());
		currentAnimation->setScale(target->getGlobalScale());
		//Debug::print("Animation: " + currentAnimation->getName());
		//Debug::print("Frame: " + std::to_string(currentAnimation->getFrame()));
		currentAnimation->draw(window, playTime);
	}
}

void AnimationPlayer::start()
{
	if (currentAnimation)
	{
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
	Animation newAnimation(animationName, texturePath, hframes, frameTime);
	animations.push_back(newAnimation);
}

const Animation* AnimationPlayer::getCurrentAnimation() const
{
	return currentAnimation;
}

bool AnimationPlayer::isPlaying() const noexcept
{
	return playing;
}
