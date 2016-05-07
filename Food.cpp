#include "Food.h"

Food::Food()
{
	spriteSheet.loadFromFile("resources/spriteSheet3.png");
	sprite.setTexture(spriteSheet);
	sprite.setTextureRect(sf::IntRect(GameConstants::FOOD_SPRITEX, GameConstants::FOOD_SPRITEY, GameConstants::SHEET_TILE_SIZE, GameConstants::SHEET_TILE_SIZE));
	sprite.setScale(GameConstants::SCALE, GameConstants::SCALE);
	
}

void Food::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

void Food::setPosition(sf::Vector2f position)
{
	sprite.setPosition(position);
}
