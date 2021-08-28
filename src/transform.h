#pragma once
#include "SFML/Graphics.hpp"

/// <summary>
// Working on this
/// </summary>

class Transform
{
private:
	sf::Transform globalTransform;
	sf::Transform transform;

	sf::Vector2f globalPosition;
	float globalRotation;
	sf::Vector2f globalRotation;

	sf::Vector2f position;
	float rotation;
	sf::Vector2f scale;
};