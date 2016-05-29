#include "Pacman.h"

Pacman::Pacman()
{
	m_frameX = GameConstants::FRAME_OFFSETX;
	m_frameY = 0;
	
	m_collisionBox.setSize(sf::Vector2f(GameConstants::TILE_SIZE, GameConstants::TILE_SIZE));
	m_collisionBox.setOrigin(m_collisionBox.getGlobalBounds().width / 2, m_collisionBox.getGlobalBounds().height / 2);

	m_spawnPosition.x = GameConstants::PACMAN_SPAWNJ;
	m_spawnPosition.y = GameConstants::PACMAN_SPAWNI;
	
	m_collisionBox.setFillColor(sf::Color::Blue);
	m_sprite.setTextureRect(sf::IntRect(m_frameX, m_frameY, GameConstants::FRAME_WIDTH, GameConstants::FRAME_HEIGHT));

	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setScale(GameConstants::SCALE, GameConstants::SCALE);
	m_sprite.setPosition(m_collisionBox.getGlobalBounds().left + m_collisionBox.getGlobalBounds().width / 2, m_collisionBox.getGlobalBounds().top + m_collisionBox.getGlobalBounds().height / 2);

	m_movingState = NOWHERE;

	int speedDenominator = GameConstants::PACMAN_SPEED_DENOMINATOR;
	m_speed = (float)1 / speedDenominator;

	isAlive = true;
}

void Pacman::changeDirection()
{	
	// Меняем направление в зависимости от нажатой клавиши
	if (isAlive)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (m_isRightFree)
			{
				m_movingState = RIGHT;
				m_sprite.setRotation(0);
			}

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (m_isLeftFree)
			{
				m_movingState = LEFT;
				m_sprite.setRotation(180);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (m_isUpFree)
			{
				m_movingState = UP;
				m_sprite.setRotation(270);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (m_isDownFree)
			{
				m_movingState = DOWN;
				m_sprite.setRotation(90);
			}
		}
	}
}

void Pacman::update(sf::Clock clock)
{

	if (isAlive)
	{
		if (m_movingState == UP && m_isUpFree)
		{
			moveUp();
		}
		if (m_movingState == DOWN && m_isDownFree)
		{
			moveDown();
		}
		if (m_movingState == RIGHT && m_isRightFree)
		{
			moveRight();
		}
		if (m_movingState == LEFT && m_isLeftFree)
		{
			moveLeft();
		}

		m_sprite.setPosition(m_collisionBox.getGlobalBounds().left + m_collisionBox.getGlobalBounds().width / 2, m_collisionBox.getGlobalBounds().top + m_collisionBox.getGlobalBounds().height / 2);		
		playAnimation(clock);
	}
}

void Pacman::die()
{
	if (isAlive)
	{
		m_sprite.setRotation(0);
		isAlive = false;
		m_frameIndex = 0;
		m_movingState = NOWHERE;
	}
}

void Pacman::respawn()
{
	isAlive = true;
	m_frameX = GameConstants::FRAME_OFFSETX;
	m_frameY = 0;
	m_sprite.setTextureRect(sf::IntRect(m_frameX, m_frameY, GameConstants::FRAME_WIDTH, GameConstants::FRAME_HEIGHT));
	m_isVisible = true;
}

void Pacman::playAnimation(sf::Clock clock)
{
	float timeSinceLastFrame = clock.getElapsedTime().asMilliseconds() - m_lastFrameTime;
	if (timeSinceLastFrame > GameConstants::FRAME_DURATION)
	{
		m_lastFrameTime = clock.getElapsedTime().asMilliseconds();

		if (m_frameIndex >= GameConstants::NUMBER_OF_FRAMES - 1)
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

bool Pacman::playDeathAnimation(sf::Clock clock)
{
	bool returnValue = true;
	if (!isAlive)
	{
		float timeSinceLastFrame = clock.getElapsedTime().asMilliseconds() - m_lastFrameTime;
		if (timeSinceLastFrame > GameConstants::FRAME_DURATION)
		{

			m_lastFrameTime = clock.getElapsedTime().asMilliseconds();

			if (m_frameIndex < GameConstants::NUMBER_OF_DEATH_FRAMES)
			{
				m_frameIndex++;
			}
			else
			{
				hide();
			}
			m_frameX = GameConstants::DEATH_FRAME_OFFSETX + GameConstants::FRAME_WIDTH*m_frameIndex;
			m_sprite.setTextureRect(sf::IntRect(m_frameX, m_frameY, GameConstants::FRAME_WIDTH, GameConstants::FRAME_HEIGHT));
			if (m_frameIndex >= GameConstants::NUMBER_OF_DEATH_FRAMES)
			{
				returnValue = false;
			}
		}
	}
	return returnValue;
}
