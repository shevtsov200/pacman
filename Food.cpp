#include "Food.h"

Food::Food()
{
	m_state = PRESENT;
}

void Food::setTexture(sf::Texture & spriteSheet)
{
	m_sprite.setTexture(spriteSheet);
	m_sprite.setTextureRect(sf::IntRect(GameConstants::FOOD_SPRITEX, GameConstants::FOOD_SPRITEY, GameConstants::SHEET_TILE_SIZE, GameConstants::SHEET_TILE_SIZE));
	m_sprite.setScale(GameConstants::SCALE, GameConstants::SCALE);
}

void Food::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (m_state == PRESENT)
	{
		target.draw(m_sprite, states);
	}
}

void Food::setPosition(sf::Vector2f position)
{
	m_sprite.setPosition(position);
}

void Food::setState(states state)
{
	m_state = state;
}

sf::FloatRect Food::getCollisionRectangle()
{
	return m_sprite.getGlobalBounds();
}
