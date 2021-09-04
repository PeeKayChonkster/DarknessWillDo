#pragma once
#include "SFML/Graphics.hpp"


class Drawable
{
public:
	Drawable();
	~Drawable();

	virtual void draw(sf::RenderTarget* window) = 0;
};