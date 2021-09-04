#pragma once
#include "SFML/Graphics.hpp"
#include "glm/vec2.hpp"
#include "tools.h"
#include <string>
#include "drawable.h"
#include "animationPlayer.h"
#include "node.h"

class Entity : public Node
{
protected:
	AnimationPlayer animationPlayer;
	float maxSpeed;
public:

	Entity();
	Entity(Node* parent);
	Entity(const glm::vec2& position);
	Entity(Node* parent, const glm::vec2& position);
	Entity(const std::string& texturePath);
	Entity(const Entity& other);
	Entity& operator=(const Entity& other) = delete;
	~Entity();

	bool operator==(const Entity& other);

	void rotate(glm::vec2 direction, float speed);

	virtual void start() override;
	virtual void update(float delta) override;

};