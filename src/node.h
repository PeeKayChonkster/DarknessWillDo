#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include "glm/vec2.hpp"
#include <vector>

class Node : public sf::Transformable
{
private:
	static const std::string type;
	std::vector<Node*> children;
	Node* parent;
public:
	Node();
	Node(Node* parent);
	Node(const glm::vec2& position);
	Node(Node* parent, const glm::vec2& position);
	~Node();

	void addChild(Node* node);
	inline void removeChild(Node* node);

	virtual void start();
	virtual void update(float deltaTime);

	// setters/getters //
	void setPosition(const glm::vec2& vec);
	void setRotation(float angle);
	void setScale(const glm::vec2& vec);
	void move(const glm::vec2& vec);
	std::vector<Node*>* getChildren();
	Node* getChild(unsigned int index);

	glm::vec2 getPosition() const noexcept;
	float getRotation() const noexcept;
	glm::vec2 getScale() const noexcept;
	Node* getParent() const noexcept;
	////////////////////
};

