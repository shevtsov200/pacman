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

	setInitialPosition(sf::Vector2i(GameConstants::GHOST_SPAWNI, GameConstants::GHOST_SPAWNJ));
	//m_collisionBox.setPosition(GameConstants::GHOST_SPAWNX + m_collisionBox.getOrigin().x, GameConstants::GHOST_SPAWNY + m_collisionBox.getOrigin().y);

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

	m_lastTilePosition.x = 0;
	m_lastTilePosition.y = 0;
}
void Enemy::findPath()
{
	changeDirection();

	sf::Vector2f pixelPosition;
	sf::Vector2i tilePosition;

	if (m_movingState == UP)
	{
		//pixelPosition.y = -m_speed;
		//m_lastTilePosition = m_tilePosition;
		//m_pixelPosition.y = m_pixelPosition.y - m_speed;
		//m_tilePosition.y = pixelsToIndexes
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

}

void Enemy::changeDirection()
{
	//if ((m_tilePosition.x != m_last) || (m_characterJ != m_lastCharacterJ))
	if(m_tilePosition != m_lastTilePosition)
	{

		sf::Vector2i tmp;
		//tmp.x = m_target.x - m_tilePosition.y;
		//tmp.y = m_target.y - m_tilePosition.x;

		tmp = m_target - m_tilePosition;

		int tmpMax = std::max(abs(tmp.x), abs(tmp.y));

		//if ((m_target.y == m_characterJ) && (m_target.x == m_characterI) && (m_movingState != NOWHERE))
		if((m_target == m_tilePosition) && (m_movingState != NOWHERE))
		{
			stop();
		}
		else if (tmpMax == abs(tmp.x))
		{
			changeHorizontalDirection();
		}
		else if (tmpMax == abs(tmp.y))
		{
			changeVerticalDirection();
		}

		m_lastTilePosition = m_tilePosition;
	}
}

/*void Enemy::changeDirection()
{
	if (m_testMovingUp && (m_movingState != DOWN))
	{
	m_movingState = UP;
	}
	else if (m_testMovingLeft && (m_movingState != RIGHT))
	{
	m_movingState = LEFT;
	}
	else if (m_testMovingDown && (m_movingState != UP))
	{
	m_movingState = DOWN;
	}
	else if (m_testMovingRight && (m_movingState != LEFT))
	{
	m_movingState = RIGHT;
	}
}*/

void Enemy::changeHorizontalDirection()
{
	if (m_tilePosition.y < m_target.y )
	{
		if (m_testMovingRight && (m_movingState != LEFT))
		{
			m_movingState = RIGHT;
		}
		else if (m_testMovingUp && (m_movingState != DOWN))
		{
			m_movingState = UP;
		}
		else if (m_testMovingLeft && (m_movingState !=RIGHT ))
		{
			m_movingState = LEFT;
		}
		else if (m_testMovingDown && (m_movingState != UP))
		{
			m_movingState = DOWN;
		}
	}

	else if ((m_tilePosition.y > m_target.y))
	{
		if (m_testMovingLeft && (m_movingState != RIGHT))
		{
			m_movingState = LEFT;
		}
		else if (m_testMovingDown && (m_movingState != UP))
		{
			m_movingState = DOWN;
		}
		else if (m_testMovingRight && (m_movingState != LEFT ))
		{
			m_movingState = RIGHT;
		}
		else if (m_testMovingUp && (m_movingState != DOWN))
		{
			m_movingState = UP;
		}
		

	}
	else if (m_testMovingDown && (m_movingState != UP))
	{
		m_movingState = DOWN;
	}
	else if (m_testMovingUp && (m_movingState != DOWN))
	{
		m_movingState = UP;
	}
}

void Enemy::changeVerticalDirection()
{
	if ((m_tilePosition.x < m_target.x))
	{
		if (m_testMovingDown && (m_movingState != UP))
		{
			m_movingState = DOWN;
		}
		else if (m_testMovingRight && (m_movingState != LEFT))
		{
			m_movingState = RIGHT;
		}
		else if (m_testMovingUp && (m_movingState != DOWN))
		{
			m_movingState = UP;
		}
		else if (m_testMovingLeft && (m_movingState != RIGHT))
		{
			m_movingState = LEFT;
		}

	}
	else if ((m_tilePosition.x > m_target.x))
	{
		if (m_testMovingUp && (m_movingState != DOWN))
		{
			m_movingState = UP;
		}
		else if (m_testMovingLeft && (m_movingState != RIGHT))
		{
			m_movingState = LEFT;
		}
		else if (m_testMovingDown && (m_movingState != UP))
		{
			m_movingState = DOWN;
		}
		else if (m_testMovingRight && (m_movingState != LEFT))
		{
			m_movingState = RIGHT;
		}
	}
	else if (m_testMovingRight && (m_movingState != LEFT))
	{
		m_movingState = RIGHT;
	}
	else if (m_testMovingLeft && (m_movingState != RIGHT))
	{
		m_movingState = LEFT;
	}
}


void Enemy::update(sf::Clock clock)
{
	//changeDirection();
	/*if (m_movingState == UP)
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
	}*/

	m_sprite.setPosition(m_collisionBox.getGlobalBounds().left + m_collisionBox.getGlobalBounds().width / 2, m_collisionBox.getGlobalBounds().top + m_collisionBox.getGlobalBounds().height / 2);

	m_collisionBoxCenter.setPosition(m_collisionBox.getGlobalBounds().left + m_collisionBox.getOrigin().x, m_collisionBox.getGlobalBounds().top + m_collisionBox.getOrigin().y);

}

void Enemy::update()
{
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


void Enemy::setTarget(sf::Vector2i target)
{
	m_target = target;
}

sf::Vector2i Enemy::getTarget()
{
	return m_target;
}
