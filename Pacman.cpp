#include "Pacman.h"

Pacman::Pacman()
{
	spriteSheet.loadFromFile("spriteSheet.png");

	sprite.setTexture(spriteSheet);
	sprite.setTextureRect(sf::IntRect(473, 0, 15, 15));
	sprite.setPosition(50, 50);
}
void Pacman::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}
