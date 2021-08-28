#pragma once
#include <vector>
#include <string>
#include "animation.h"
#include "drawable.h"
#include "runnable.h"
#include "SFML/Graphics.hpp"
#include "node.h"

class AnimationPlayer : public Drawable, public Runnable, public Node
{
private:
	std::vector<Animation> animations;
	float playTime;
	bool playing;
	Animation* currentAnimation;
public:
	bool loop;

	AnimationPlayer();
	~AnimationPlayer();

	void play(const std::string& animationName, bool looping = true);
	void stop();
	void draw(sf::RenderWindow* window) override;
	void start() override;
	void update(float delta) override;
	void createAnimation(std::string animationName, const std::string& texturePath, unsigned int hframes, float frameTime);
	bool isPlaying() const noexcept;
};

