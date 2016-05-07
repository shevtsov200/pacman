#pragma once
#include "SFML/Graphics.hpp"
#include "GameConstants.h"
class Food : public sf::Drawable, public sf::Transformable
{
public:
	Food();
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void setPosition(sf::Vector2f position);

private:
	sf::Sprite sprite;
	sf::Texture spriteSheet;
};