#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include "glm/vec2.hpp"
#include <vector>

class Node
{
protected:
	static const std::string type;
	std::vector<Node*> children;
	Node* parent;
public:
	Node();
	Node(Node* parent);
	virtual ~Node();

	void addChild(Node* node);
	void removeChild(Node* node);

	virtual void start();
	virtual void update(float deltaTime);

	// setters/getters //
	std::vector<Node*>* getChildren();
	Node* getChild(unsigned int index);
	Node* getParent() const noexcept;
	////////////////////
};

