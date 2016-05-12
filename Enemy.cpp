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
	m_collisionBox.setPosition(GameConstants::GHOST_SPAWNX + m_collisionBox.getOrigin().x,GameConstants::GHOST_SPAWNY + m_collisionBox.getOrigin().y);
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

	static bool seeded = false;
	if (!seeded)
	{
		std::srand(std::time(0));
		seeded = true;
	}

}
void Enemy::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);

	if (GameConstants::IS_DEBUGGING)
	{
		target.draw(m_collisionBox, states);
		target.draw(m_collisionBoxCenter, states);
	}
	//target.draw(m_target, states);
}

void Enemy::changeDirection(int targetI, int targetJ, int enemyI, int enemyJ)
{
	sf::Vector2i tmp;
	tmp.x = targetJ - enemyJ;
	tmp.y = targetI - enemyI;
	int tmpMax = std::max(abs(tmp.x), abs(tmp.y));
	

	if ((tmpMax == tmp.x) && (m_testMovingLeft || m_testMovingRight))
	{
		if ((enemyJ < targetJ) && m_testMovingRight)
		{
			m_movingState = RIGHT;
		}

		else if ((enemyJ > targetJ) && m_testMovingLeft)
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
	else if ((tmpMax == tmp.y) && (m_testMovingDown || m_testMovingUp))
	{
		if ((enemyI < targetI) && m_testMovingDown)
		{
			m_movingState = DOWN;
		}
		else if ((enemyI > targetI) && m_testMovingUp)
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
	else if(m_testMovingUp)
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
	
}

void Enemy::changeVerticalDirection(int targetI, int enemyI)
{

}

void Enemy::moveRight()
{
	m_collisionBox.move(m_speed, 0);
}

void Enemy::moveLeft()
{
	m_collisionBox.move(-m_speed, 0);
}

void Enemy::moveUp()
{
	m_collisionBox.move(0, -m_speed);
}

void Enemy::moveDown()
{
	m_collisionBox.move(0, m_speed);
}

void Enemy::stop()
{
	m_velocity.x = 0;
	m_velocity.y = 0;
}

void Enemy::update(sf::Clock clock)
{
	//changeDirection();
	if (m_movingState == UP && m_testMovingUp)
	{
		moveUp();
	}
	if (m_movingState == DOWN && m_testMovingDown)
	{
		moveDown();
	}
	if (m_movingState == RIGHT && m_testMovingRight)
	{
		moveRight();
	}
	if (m_movingState == LEFT && m_testMovingLeft)
	{
		moveLeft();
	}

	m_sprite.setPosition(m_collisionBox.getGlobalBounds().left + m_collisionBox.getGlobalBounds().width / 2, m_collisionBox.getGlobalBounds().top + m_collisionBox.getGlobalBounds().height / 2);

	m_collisionBoxCenter.setPosition(m_collisionBox.getGlobalBounds().left + m_collisionBox.getOrigin().x, m_collisionBox.getGlobalBounds().top + m_collisionBox.getOrigin().y);

	playAnimation(clock);
}

void Enemy::playAnimation(sf::Clock clock)
{
	/*float timeSinceLastFrame = clock.getElapsedTime().asMilliseconds() - m_lastFrameTime;
	if (timeSinceLastFrame > GameConstants::FRAME_DURATION)
	{

		m_lastFrameTime = clock.getElapsedTime().asMilliseconds();

		if (m_frameIndex == GameConstants::NUMBER_OF_FRAMES - 1)
		{
			m_frameIndex = 0;
		}
		else
		{
			m_frameIndex++;
		}
		m_frameX = GameConstants::FRAME_OFFSETX + GameConstants::FRAME_WIDTH*m_frameIndex;
		m_sprite.setTextureRect(sf::IntRect(m_frameX, m_frameY, GameConstants::FRAME_WIDTH, GameConstants::FRAME_HEIGHT));
	}*/
}

void Enemy::setFreePathState(directionStates freePathState)
{
	//m_freePathState = freePathState;
}

sf::RectangleShape Enemy::getCollisionBox()
{
	return m_collisionBox;
}
