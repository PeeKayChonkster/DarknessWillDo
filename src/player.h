#pragma once
#include "SFML/Graphics.hpp"
#include "entity.h"
#include <string>
#include "animationPlayer.h"
#include "audioPlayer.h"
#include "timer.h"
#include "bullet.h"
#include <array>

class Player : public Entity
{
private:
	static const std::string type;
	glm::vec2 moveTarget;
	AudioPlayer audioPlayer;
	std::vector<sf::Event> windowEvents;
	Timer timer;
	std::vector<Bullet*> bullets;
public:
	Player();
	Player(const std::string& texturePath);
	Player(const Player&) = delete;
	Player(const glm::vec2& position);
	~Player();
	Player& operator=(const Player&) = delete;
	void getInput(float delta);
	void pushEvent(sf::Event event);

	void shoot(glm::vec2 velocity);

	virtual void start() override;
	virtual void update(float delta) override;
};