#pragma once
#include "node.h"

class Node2D : public Node, public sf::Transformable
{
private:

public:
	Node2D();
	Node2D(Node* parent);
	Node2D(glm::vec2 position);
	Node2D(Node* parent, glm::vec2 position);

	virtual void start() override;
	virtual void update(float deltaTime) override;

	// setters/getters //
	void setPosition(const glm::vec2& vec);
	void setRotation(float angle);
	void setScale(const glm::vec2& vec);
	void move(const glm::vec2& vec);

	glm::vec2 getPosition() const noexcept;
	glm::vec2 getGlobalPosition() const noexcept;
	float getRotation() const noexcept;
	float getGlobalRotation() const noexcept;
	glm::vec2 getScale() const noexcept;
	glm::vec2 getGlobalScale() const noexcept;
};