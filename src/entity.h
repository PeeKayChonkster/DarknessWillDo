#pragma once
#include "SFML/Graphics.hpp"
#include "glm/vec2.hpp"
#include "tools.h"
#include <string>
#include "runnable.h"
#include "drawable.h"
#include "animationPlayer.h"
#include "node.h"

class Entity : public Runnable, public Node
{
protected:
	AnimationPlayer animationPlayer;
	float maxSpeed;
public:

	Entity() = delete;
	Entity(const std::string& texturePath);
	Entity(const Entity& other);
	Entity& operator=(const Entity& other) = delete;
	~Entity();

	bool operator==(const Entity& other);

	virtual void start() override;
	virtual void update(float delta) override;

};