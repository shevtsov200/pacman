#include <cstdlib>
#include <iostream>
#include "Enemy.h"
#include "GameConstants.h"
Enemy::Enemy()
{
	m_frameX = GameConstants::GHOST_SPRITEX;
	m_frameY = GameConstants::GHOST_SPRITEY;

	m_collisionBox.setSize(sf::Vector2f(GameConstants::TILE_SIZE, GameConstants::TILE_SIZE));

	m_collisionBox.setOrigin(m_collisionBox.getGlobalBounds().width / 2, m_collisionBox.getGlobalBounds().height / 2);

	m_collisionBox.setFillColor(sf::Color::Blue);

	m_sprite.setTextureRect(sf::IntRect(m_frameX, m_frameY, GameConstants::GHOST_SPRITE_WIDTH, GameConstants::GHOST_SPRITE_HEIGHT));

	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setScale(GameConstants::SCALE, GameConstants::SCALE);
	m_sprite.setPosition(m_collisionBox.getGlobalBounds().left + m_collisionBox.getGlobalBounds().width / 2, m_collisionBox.getGlobalBounds().top + m_collisionBox.getGlobalBounds().height / 2);

	m_speed = 0;
	m_movingState = NOWHERE;

	m_isUpFree = false;
	m_isDownFree = false;
	m_isLeftFree = false;
	m_isRightFree = false;

	int speedDenominator = GameConstants::BLINKY_SPEED_DENOMINATOR;
	m_speed = (float)1 / speedDenominator;

	setName("Blinky");
}

void Enemy::changeDirection()
{
	if(m_tilePosition != m_checkTile)
	{
		sf::Vector2i tmp;

		tmp = m_target - m_tilePosition;

		int tmpMax = std::max(abs(tmp.y), abs(tmp.x));

		if (tmpMax == abs(tmp.y))
		{
			changeVerticalDirection();
		}
		else if (tmpMax == abs(tmp.x))
		{
			changeHorizontalDirection();
		}
		m_checkTile = m_tilePosition;
	}
}

void Enemy::changeHorizontalDirection()
{
	if (m_tilePosition.x < m_target.x )
	{
		if (m_isRightFree && (m_movingState != LEFT))
		{
			m_movingState = RIGHT;
		}
		else if (m_isUpFree && (m_movingState != DOWN))
		{
			m_movingState = UP;
		}
		else if (m_isLeftFree && (m_movingState !=RIGHT ))
		{
			m_movingState = LEFT;
		}
		else if (m_isDownFree && (m_movingState != UP))
		{
			m_movingState = DOWN;
		}
	}
	else if ((m_tilePosition.x > m_target.x))
	{
		if (m_isLeftFree && (m_movingState != RIGHT))
		{
			m_movingState = LEFT;
		}
		else if (m_isDownFree && (m_movingState != UP))
		{
			m_movingState = DOWN;
		}
		else if (m_isRightFree && (m_movingState != LEFT ))
		{
			m_movingState = RIGHT;
		}
		else if (m_isUpFree && (m_movingState != DOWN))
		{
			m_movingState = UP;
		}
	}
	else if (m_isDownFree && (m_movingState != UP))
	{
		m_movingState = DOWN;
	}
	else if (m_isUpFree && (m_movingState != DOWN))
	{
		m_movingState = UP;
	}
}

void Enemy::changeVerticalDirection()
{
	if ((m_tilePosition.y < m_target.y))
	{
		if (m_isDownFree && (m_movingState != UP))
		{
			m_movingState = DOWN;
		}
		else if (m_isRightFree && (m_movingState != LEFT))
		{
			m_movingState = RIGHT;
		}
		else if (m_isUpFree && (m_movingState != DOWN))
		{
			m_movingState = UP;
		}
		else if (m_isLeftFree && (m_movingState != RIGHT))
		{
			m_movingState = LEFT;
		}

	}
	else if ((m_tilePosition.y > m_target.y))
	{
		if (m_isUpFree && (m_movingState != DOWN))
		{
			m_movingState = UP;
		}
		else if (m_isLeftFree && (m_movingState != RIGHT))
		{
			m_movingState = LEFT;
		}
		else if (m_isDownFree && (m_movingState != UP))
		{
			m_movingState = DOWN;
		}
		else if (m_isRightFree && (m_movingState != LEFT))
		{
			m_movingState = RIGHT;
		}
	}
	else if (m_isRightFree && (m_movingState != LEFT))
	{
		m_movingState = RIGHT;
	}
	else if (m_isLeftFree && (m_movingState != RIGHT))
	{
		m_movingState = LEFT;
	}
}

void Enemy::update()
{
	if (m_movingState == UP)
	{
		moveUp();
	}
	else if (m_movingState == DOWN)
	{
		moveDown();
	}
	else if (m_movingState == RIGHT)
	{
		moveRight();
	}
	else if (m_movingState == LEFT)
	{
		moveLeft();
	}

	updateSprite();

	m_sprite.setPosition(m_collisionBox.getGlobalBounds().left + m_collisionBox.getGlobalBounds().width / 2, m_collisionBox.getGlobalBounds().top + m_collisionBox.getGlobalBounds().height / 2);
}

void Enemy::updateSprite()
{
	
	if (m_movingState == UP)
	{
		m_frameX = GameConstants::GHOST_UPX;
		m_frameY = m_frameOffsetY + GameConstants::GHOST_UPY;

	}
	else if (m_movingState == LEFT)
	{
		m_frameX = GameConstants::GHOST_LEFTX;
		m_frameY = m_frameOffsetY + GameConstants::GHOST_LEFTY;
	}
	else if (m_movingState == DOWN)
	{
		m_frameX = GameConstants::GHOST_DOWNX;
		m_frameY = m_frameOffsetY + GameConstants::GHOST_DOWNY;
	}
	else
	{
		m_frameX = GameConstants::GHOST_RIGHTX;
		m_frameY = m_frameOffsetY + GameConstants::GHOST_RIGHTY;
	}
	m_sprite.setTextureRect(sf::IntRect(m_frameX, m_frameY, GameConstants::FRAME_WIDTH, GameConstants::FRAME_HEIGHT));
}

void Enemy::setName(std::string name)
{
	m_spawnPosition.x = 0;
	m_spawnPosition.y = 0;
	m_name = name;
	if (m_name == "Blinky")
	{
		m_frameOffsetY = 0;
		m_spawnPosition.x = 11;
		m_spawnPosition.y = 11;

	}
	else if (m_name == "Pinky")
	{
		m_frameOffsetY = GameConstants::FRAME_HEIGHT;
		m_spawnPosition.x = 13;
		m_spawnPosition.y = 11;
	}
	else if (m_name == "Inky")
	{
		m_frameOffsetY = GameConstants::FRAME_HEIGHT * 2;
		m_spawnPosition.x = 15;
		m_spawnPosition.y = 11;
	}
	else if (m_name == "Clyde")
	{
		m_frameOffsetY = GameConstants::FRAME_HEIGHT * 3;
		m_spawnPosition.x = 16;
		m_spawnPosition.y = 11;
	}
	setInitialPosition();
}


void Enemy::setTarget(sf::Vector2i target, directionStates direction)
{
	if (m_name == "Blinky")
	{
		setBlinkyTarget(target);
	}
	else if (m_name == "Pinky")
	{
		setPinkyTarget(target, direction);
	}
	else if (m_name == "Inky")
	{
		setInkyTarget(target, direction);
	}
	else if (m_name == "Clyde")
	{
		setClydeTarget(target);
	}
}



void Enemy::setTarget(sf::Vector2i target)
{
	m_target = target;

}

void Enemy::setBlinkyTarget(sf::Vector2i target)
{
	m_target = target;
}

void Enemy::setPinkyTarget(sf::Vector2i target, directionStates direction)
{
	sf::Vector2i tmpTarget;
	if (direction == UP)
	{
		tmpTarget.x = target.x;
		tmpTarget.y = target.y - 4;
	}
	else if (direction == LEFT)
	{
		tmpTarget.x = target.x - 4;
		tmpTarget.y = target.y;
	}
	else if (direction == DOWN)
	{
		tmpTarget.x = target.x;
		tmpTarget.y = target.y + 4;
	}
	else if (direction == RIGHT)
	{
		tmpTarget.x = target.x + 4;
		tmpTarget.y = target.y;
	}
	else if (direction == NOWHERE)
	{
		tmpTarget = target;
	}

	if (tmpTarget.x < 0)
	{
		tmpTarget.x = 0;
	}
	else if (tmpTarget.x > GameConstants::MAZE_WIDTH -1)
	{
		tmpTarget.x = GameConstants::MAZE_WIDTH -1;
	}

	if (tmpTarget.y < 0)
	{
		tmpTarget.y = 0;
	}
	else if (tmpTarget.y > GameConstants::MAZE_HEIGHT - 1)
	{
		tmpTarget.y = GameConstants::MAZE_HEIGHT -1;
	}

	m_target = tmpTarget;
}

void Enemy::setInkyTarget(sf::Vector2i target, directionStates direction)
{
	sf::Vector2i tmpTarget;
	if (direction == UP)
	{
		tmpTarget.x = target.x;
		tmpTarget.y = target.y + 4;

	}
	else if (direction == LEFT)
	{
		tmpTarget.x = target.x + 4;
		tmpTarget.y = target.y;
	}
	else if (direction == DOWN)
	{
		tmpTarget.x = target.x;
		tmpTarget.y = target.y - 4;
	}
	else if (direction == RIGHT)
	{
		tmpTarget.x = target.x - 4;
		tmpTarget.y = target.y;

	}
	else if (direction == NOWHERE)
	{
		tmpTarget = target;
	}

	if (tmpTarget.x < 0)
	{
		tmpTarget.x = 0;
	}
	else if (tmpTarget.x > GameConstants::MAZE_WIDTH -1)
	{
		tmpTarget.x = GameConstants::MAZE_WIDTH -1;
	}

	if (tmpTarget.y < 0)
	{
		tmpTarget.y = 0;
	}
	else if (tmpTarget.y > GameConstants::MAZE_HEIGHT -1)
	{
		tmpTarget.y = GameConstants::MAZE_HEIGHT -1;
	}

	m_target = tmpTarget;
}

void Enemy::setClydeTarget(sf::Vector2i target)
{
	if ( (abs(m_tilePosition.x - target.x) >= 8) || (abs(m_tilePosition.y - target.y) >= 8) )
	{
		m_target = target;
	}
	else
	{
		m_target.x = GameConstants::MAZE_WIDTH;
		m_target.y = GameConstants::MAZE_WIDTH;
	}
}

sf::Vector2i Enemy::getTarget()
{
	return m_target;
}
