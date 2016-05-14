#include "Character.h"
#include <iostream>
Character::Character()
{

	m_spriteSheet.loadFromFile("resources/spriteSheet3.png");

	m_sprite.setTexture(m_spriteSheet);

	m_lastFrameTime = 0;

	
	m_velocity.x = 0;
	m_velocity.y = 0;
	m_speed = (float)1 / GameConstants::SPEED_DENOMINATOR;

	m_movingState = NOWHERE;

	m_testMovingUp = false;
	m_testMovingDown = false;
	m_testMovingLeft = false;
	m_testMovingRight = false;
}

void Character::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);

	if (GameConstants::IS_DEBUGGING)
	{
		target.draw(m_collisionBox, states);
		target.draw(m_collisionBoxCenter, states);
	}
}

void Character::changeDirection()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (m_testMovingRight)
		{
			m_movingState = RIGHT;
			m_sprite.setRotation(0);
		}

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (m_testMovingLeft)
		{
			m_movingState = LEFT;
			m_sprite.setRotation(180);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (m_testMovingUp)
		{
			m_movingState = UP;
			m_sprite.setRotation(270);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (m_testMovingDown)
		{
			m_movingState = DOWN;
			m_sprite.setRotation(90);
		}
	}
}

void Character::moveRight()
{
	m_collisionBox.move(m_speed, 0);
}

void Character::moveLeft()
{
	m_collisionBox.move(-m_speed, 0);
}

void Character::moveUp()
{
	m_collisionBox.move(0, -m_speed);
}

void Character::moveDown()
{
	m_collisionBox.move(0, m_speed);
}
void Character::stop()
{
	m_velocity.x = 0;
	m_velocity.y = 0;
}

void Character::update(sf::Clock clock)
{
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

void Character::playAnimation(sf::Clock clock)
{
	float timeSinceLastFrame = clock.getElapsedTime().asMilliseconds() - m_lastFrameTime;
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
	}
}
sf::RectangleShape Character::getCollisionBox()
{
	return m_collisionBox;
}

