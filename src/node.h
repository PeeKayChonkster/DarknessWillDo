#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include "glm/vec2.hpp"

class Node : public sf::Transformable
{
private:
	std::vector<Node*> children;
	Node* parent;
public:
	Node();
	Node(Node* parent);
	~Node();

	void addChild(Node* node);
	inline void removeChild(Node* node);

	// setters/getters //
	void setPosition(const glm::vec2& vec);
	void setRotation(float angle);
	void setScale(const glm::vec2& vec);
	void move(const glm::vec2& vec);

	void setParent(Node* node);
	glm::vec2 getPosition() const noexcept;
	float getRotation() const noexcept;
	glm::vec2 getScale() const noexcept;
	Node* getParent() const noexcept;
	////////////////////
};

