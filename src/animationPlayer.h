#pragma once
#include <vector>
#include <string>
#include "animation.h"
#include "drawable.h"
#include "SFML/Graphics.hpp"
#include "node.h"

class Node2D;

class AnimationPlayer : public Drawable, public Node
{
private:
	static const std::string type;
	const Node2D* target;
	std::vector<Animation> animations;
	float playTime;
	bool playing;
	bool allowedToInterrupt;
	Animation* currentAnimation;
public:
	bool loop;

	AnimationPlayer(const Node2D* target);
	~AnimationPlayer();

	void play(const std::string& animationName, bool looping = true, bool interruptable = true);
	void stop();
	void draw(sf::RenderTarget* window) override;
	void start() override;
	void update(float delta) override;
	void createAnimation(std::string animationName, const std::string& texturePath, unsigned int hframes, float frameTime);
	const Animation* getCurrentAnimation() const;
	bool isPlaying() const noexcept;
};

