#include "Pacman.h"

Pacman::Pacman()
{


	m_frameX = GameConstants::FRAME_OFFSETX;
	m_frameY = 0;
	
	m_collisionBox.setSize(sf::Vector2f(GameConstants::TILE_SIZE, GameConstants::TILE_SIZE));

	m_collisionBox.setOrigin(m_collisionBox.getGlobalBounds().width / 2, m_collisionBox.getGlobalBounds().height / 2);

	//m_collisionBox.setPosition(GameConstants::PACMAN_SPAWNX + m_collisionBox.getOrigin().x, GameConstants::PACMAN_SPAWNY + m_collisionBox.getOrigin().y);
	setInitialPosition(sf::Vector2i(GameConstants::PACMAN_SPAWNI, GameConstants::PACMAN_SPAWNJ));
	

	m_collisionBox.setFillColor(sf::Color::Blue);

	m_collisionBoxCenter.setSize(sf::Vector2f(4, 4));
	m_collisionBoxCenter.setPosition(m_collisionBox.getGlobalBounds().left + m_collisionBox.getOrigin().x - m_collisionBoxCenter.getGlobalBounds().width/2, m_collisionBox.getGlobalBounds().top + m_collisionBox.getOrigin().y - m_collisionBoxCenter.getGlobalBounds().height / 2);
	m_collisionBoxCenter.setFillColor(sf::Color::Yellow);

	m_sprite.setTextureRect(sf::IntRect(m_frameX, m_frameY, GameConstants::FRAME_WIDTH, GameConstants::FRAME_HEIGHT));

	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setScale(GameConstants::SCALE, GameConstants::SCALE);
	m_sprite.setPosition(m_collisionBox.getGlobalBounds().left + m_collisionBox.getGlobalBounds().width / 2, m_collisionBox.getGlobalBounds().top + m_collisionBox.getGlobalBounds().height / 2);

	//m_characterJ = xToJ(getCollisionBox().getGlobalBounds().left + getCollisionBox().getOrigin().x);
	//m_characterI = yToI(getCollisionBox().getGlobalBounds().top + getCollisionBox().getOrigin().y);
	m_tilePosition = pixelsToIndexes(sf::Vector2f(getCollisionBox().getGlobalBounds().left + getCollisionBox().getOrigin().x,
		getCollisionBox().getGlobalBounds().top + getCollisionBox().getOrigin().y));
	//setCurrentTilePosition(GameConstants::TILE_SIZE*m_tilePosition.x, GameConstants::TILE_SIZE*m_tilePosition.y);


	m_movingState = NOWHERE;

	isAlive = true;

}

void Pacman::changeDirection()
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

void Pacman::update(sf::Clock clock)
{

	if (isAlive)
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

		//m_currentTile.setPosition(m_tilePosition.y*GameConstants::TILE_SIZE, m_tilePosition.x*GameConstants::TILE_SIZE);
		//updateCurrentTilePosition();
		m_sprite.setPosition(m_collisionBox.getGlobalBounds().left + m_collisionBox.getGlobalBounds().width / 2, m_collisionBox.getGlobalBounds().top + m_collisionBox.getGlobalBounds().height / 2);

		m_collisionBoxCenter.setPosition(m_collisionBox.getGlobalBounds().left + m_collisionBox.getOrigin().x - m_collisionBoxCenter.getGlobalBounds().width / 2, m_collisionBox.getGlobalBounds().top + m_collisionBox.getOrigin().y - m_collisionBoxCenter.getGlobalBounds().height / 2);
		
		playAnimation(clock);
	}
	else
	{
		playDeathAnimation(clock);
	}

}

void Pacman::Die()
{
	if (isAlive)
	{
		m_sprite.setRotation(0);
		isAlive = false;
		m_frameIndex = 0;
	}
}

void Pacman::playDeathAnimation(sf::Clock clock)
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
	}
}
