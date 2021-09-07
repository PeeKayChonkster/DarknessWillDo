#include "Node2D.h"
#include "SFML/Graphics.hpp"
#include "tools.h"

Node2D::Node2D(): Node2D(nullptr, glm::vec2(0.0f, 0.0f))
{
}

Node2D::Node2D(Node* parent): Node2D(parent, glm::vec2(0.0f, 0.0f))
{
}

Node2D::Node2D(glm::vec2 position): Node2D(nullptr, position)
{
	setPosition(position);
}

Node2D::Node2D(Node* parent, glm::vec2 position): Node(parent)
{
	setPosition(position);
}

void Node2D::start()
{
}

void Node2D::update(float deltaTime)
{
}

// setters/getters //
void Node2D::setPosition(const glm::vec2& vec)
{
	sf::Transformable::setPosition(chonky::glm_to_sf_vec(vec));

}
void Node2D::setRotation(float angle)
{
	sf::Transformable::setRotation(angle);
}
void Node2D::setScale(const glm::vec2& vec)
{
	sf::Transformable::setScale(chonky::glm_to_sf_vec(vec));
}
void Node2D::move(const glm::vec2& vec)
{
	sf::Transformable::move(chonky::glm_to_sf_vec(vec));
}

glm::vec2 Node2D::getPosition() const noexcept
{
	return chonky::sf_to_glm_vec(sf::Transformable::getPosition());
}
glm::vec2 Node2D::getGlobalPosition() const noexcept
{
	if (parent && std::is_base_of<Node2D, decltype(parent)>()) return getPosition() + static_cast<Node2D*>(parent)->getGlobalPosition();
	else return getPosition();
}
float Node2D::getRotation() const noexcept
{
	return sf::Transformable::getRotation();
}
float Node2D::getGlobalRotation() const noexcept
{
	if (parent && std::is_base_of<Node2D, decltype(parent)>()) return getRotation() + static_cast<Node2D*>(parent)->getGlobalRotation();
	else return getRotation();
}
glm::vec2 Node2D::getScale() const noexcept
{
	return chonky::sf_to_glm_vec(sf::Transformable::getScale());
}
glm::vec2 Node2D::getGlobalScale() const noexcept
{
	if (parent && std::is_base_of<Node2D, decltype(parent)>()) return getScale() * static_cast<Node2D*>(parent)->getGlobalScale();
	else return getScale();
}