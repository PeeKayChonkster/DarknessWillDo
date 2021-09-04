#pragma once
#include "glm/vec2.hpp"
#include "drawable.h"
#include "entity.h"

class Bullet : public Entity
{
private:
	static const std::string type;
	glm::vec2 direction;
	glm::vec2 initialPosition;
	float maxDistance = 5000.0f;
	float speed = 2000.0f;
	bool fired = false;
public:
	Bullet();
	Bullet(Node* parent, const glm::vec2& position);
	~Bullet();
	void fire(glm::vec2 velocity);
	void start() override;
	void update(float delta) override;
};