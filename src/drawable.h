#pragma once
#include "SFML/Graphics.hpp"


class Drawable
{
public:
	Drawable();
	~Drawable();

	virtual void draw(sf::RenderWindow* window) = 0;
};