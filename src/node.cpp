#include "node.h"
#include "tools.h"
#include <ranges>


Node::Node() : children(), parent(nullptr)
{
}

Node::Node(Node* parent) : parent(parent) 
{
	parent->addChild(this); 
}

Node::~Node() 
{ 
	if (parent) parent->removeChild(this); 
}

void Node::addChild(Node* node)
{
	children.push_back(node);
	node->setParent(this);
	node->setPosition(getPosition() + node->getPosition());
	node->setRotation(getRotation() + node->getRotation());
	node->setScale(getScale() * node->getScale());
}
void Node::removeChild(Node* node)
{
	if (auto result = std::ranges::find(children, node); result != children.end())
	{
		children.erase(result);
	}
}

// setters/getters //
void Node::setPosition(const glm::vec2& vec)
{
	sf::Transformable::setPosition(chonky::glm_to_sf_vec(vec));
	for (auto& c : children)
	{
		c->setPosition(getPosition());
	}
}
void Node::setRotation(float angle)
{
	sf::Transformable::setRotation(angle);
	for (auto& c : children)
	{
		c->setRotation(getRotation());
	}
}
void Node::setScale(const glm::vec2& vec)
{
	sf::Transformable::setScale(chonky::glm_to_sf_vec(vec));
	for (auto& c : children)
	{
		c->setScale(getScale());
	}
}
void Node::move(const glm::vec2& vec)
{
	sf::Transformable::move(chonky::glm_to_sf_vec(vec));
	for (auto& c : children)
	{
		c->move(vec);
	}
}
void Node::setParent(Node* node)
{
	if (parent) parent->removeChild(node);
	parent = node;
}

glm::vec2 Node::getPosition() const noexcept
{
	return chonky::sf_to_glm_vec(sf::Transformable::getPosition());
}
float Node::getRotation() const noexcept
{
	return sf::Transformable::getRotation();
}
glm::vec2 Node::getScale() const noexcept
{
	return chonky::sf_to_glm_vec(sf::Transformable::getScale());
}
Node* Node::getParent() const noexcept
{
	return parent;
}
////////////////////