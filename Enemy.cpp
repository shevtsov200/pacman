#include <cstdlib>
#include <iostream>
#include "Enemy.h"
#include "GameConstants.h"
Enemy::Enemy()
{
	m_spriteSheet.loadFromFile("resources/spriteSheet3.png");

	m_sprite.setTexture(m_spriteSheet);

	m_frameX = GameConstants::GHOST_SPRITEX;
	m_frameY = GameConstants::GHOST_SPRITEY;

	m_collisionBox.setSize(sf::Vector2f(GameConstants::TILE_SIZE, GameConstants::TILE_SIZE));

	m_collisionBox.setOrigin(m_collisionBox.getGlobalBounds().width / 2, m_collisionBox.getGlobalBounds().height / 2);
	m_collisionBox.setPosition(GameConstants::GHOST_SPAWNX + m_collisionBox.getOrigin().x, GameConstants::GHOST_SPAWNY + m_collisionBox.getOrigin().y);
	//m_collisionBox.setPosition(GameConstants::SPAWNX + m_collisionBox.getOrigin().x, GameConstants::SPAWNY + m_collisionBox.getOrigin().y);
	m_collisionBox.setFillColor(sf::Color::Blue);

	m_collisionBoxCenter.setSize(sf::Vector2f(4, 4));
	m_collisionBoxCenter.setPosition(m_collisionBox.getGlobalBounds().left + m_collisionBox.getOrigin().x, m_collisionBox.getGlobalBounds().top + m_collisionBox.getOrigin().y);
	m_collisionBoxCenter.setFillColor(sf::Color::Yellow);

	//m_target.setSize(sf::Vector2f(GameConstants::TILE_SIZE, GameConstants::TILE_SIZE));
	//m_target.setFillColor(sf::Color::Red);

	m_sprite.setTextureRect(sf::IntRect(m_frameX, m_frameY, GameConstants::GHOST_SPRITE_WIDTH, GameConstants::GHOST_SPRITE_HEIGHT));

	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setScale(GameConstants::SCALE, GameConstants::SCALE);
	m_sprite.setPosition(m_collisionBox.getGlobalBounds().left + m_collisionBox.getGlobalBounds().width / 2, m_collisionBox.getGlobalBounds().top + m_collisionBox.getGlobalBounds().height / 2);

	m_velocity.x = 0;
	m_velocity.y = 0;
	m_speed = (float)1 / GameConstants::SPEED_DENOMINATOR;

	m_movingState = NOWHERE;

	m_testMovingUp = false;
	m_testMovingDown = false;
	m_testMovingLeft = false;
	m_testMovingRight = false;

	
}

void Enemy::changeDirection(int targetI, int targetJ)
{
	sf::Vector2i tmp;
	tmp.x = targetJ - m_characterJ;
	tmp.y = targetI - m_characterI;
	int tmpMax = std::max(abs(tmp.x), abs(tmp.y));
	
	if (tmpMax == abs(tmp.x))
	{
		changeHorizontalDirection(targetI, targetJ);
	}
	else if (tmpMax == abs(tmp.y))
	{
		changeVerticalDirection(targetI, targetJ);
	}
	else
	{
		bool tmp = true;
	}
}

void Enemy::changeDirection()
{
	if (m_testMovingUp)
	{
		m_movingState = UP;
	}
	else if (m_testMovingLeft)
	{
		m_movingState = LEFT;
	}
	else if (m_testMovingDown)
	{
		m_movingState = DOWN;
	}
	else if (m_testMovingRight)
	{
		m_movingState = RIGHT;
	}
}

void Enemy::changeHorizontalDirection(int targetJ, int enemyJ)
{
	if ((m_characterJ < targetJ) && m_testMovingRight)
	{
		m_movingState = RIGHT;
	}

	else if ((m_characterJ > targetJ) && m_testMovingLeft)
	{
		m_movingState = LEFT;
	}
	else if (m_testMovingDown)
	{
		m_movingState = DOWN;
	}
	else if (m_testMovingUp)
	{
		m_movingState = UP;
	}
}

void Enemy::changeVerticalDirection(int targetI, int enemyI)
{
	if ((m_characterI < targetI) && m_testMovingDown)
	{
		m_movingState = DOWN;
	}
	else if ((m_characterI > targetI) && m_testMovingUp)
	{
		m_movingState = UP;
	}
	else if (m_testMovingRight)
	{
		m_movingState = RIGHT;
	}
	else if (m_testMovingLeft)
	{
		m_movingState = LEFT;
	}
}


void Enemy::update(sf::Clock clock)
{
	//changeDirection();
	if (m_movingState == UP)
	{
		moveUp();
	}
	if (m_movingState == DOWN)
	{
		moveDown();
	}
	if (m_movingState == RIGHT)
	{
		moveRight();
	}
	if (m_movingState == LEFT)
	{
		moveLeft();
	}

	m_sprite.setPosition(m_collisionBox.getGlobalBounds().left + m_collisionBox.getGlobalBounds().width / 2, m_collisionBox.getGlobalBounds().top + m_collisionBox.getGlobalBounds().height / 2);

	m_collisionBoxCenter.setPosition(m_collisionBox.getGlobalBounds().left + m_collisionBox.getOrigin().x, m_collisionBox.getGlobalBounds().top + m_collisionBox.getOrigin().y);

}
