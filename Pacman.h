#pragma once
#include <SFML\Graphics.hpp>
class Pacman : public sf::Drawable, public sf::Transformable
{
public: 
	Pacman();
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void changeDirection(sf::Event event);
	void update();

private:
	sf::Sprite sprite;
	sf::Texture spriteSheet;

	sf::Vector2f velocity;
};
