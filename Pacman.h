#pragma once
#include <SFML\Graphics.hpp>
class Pacman : public sf::Drawable, public sf::Transformable
{
public: 
	Pacman();
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
private:
	sf::Sprite sprite;
	sf::Texture spriteSheet;
};
