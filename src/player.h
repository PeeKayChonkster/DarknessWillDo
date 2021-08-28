#pragma once
#include "SFML/Graphics.hpp"
#include "entity.h"
#include <string>
#include "animationPlayer.h"
#include "audioPlayer.h"


class Player : public Entity
{
private:
	glm::vec2 moveTarget;
	AudioPlayer audioPlayer;
public:
	Player();
	Player(const std::string& texturePath);
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;
	void getInput(float delta);


	virtual void start() override;
	virtual void update(float delta) override;
};