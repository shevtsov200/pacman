#include "Pacman.h"

Pacman::Pacman()
{
	m_spriteSheet.loadFromFile("resources/spriteSheet3.png");

	m_sprite.setTexture(m_spriteSheet);

	m_frameIndex = 0;
	m_frameX = GameConstants::FRAME_OFFSETX;
	m_frameY = 0;

	m_lastFrameTime = 0;

	m_collisionBox.setSize(sf::Vector2f(GameConstants::TILE_SIZE, GameConstants::TILE_SIZE));
	
	m_collisionBox.setOrigin(m_collisionBox.getGlobalBounds().width / 2, m_collisionBox.getGlobalBounds().height / 2);
	m_collisionBox.setPosition(GameConstants::SPAWNX+m_collisionBox.getOrigin().x, GameConstants::SPAWNY + m_collisionBox.getOrigin().y);
	
	m_collisionBox.setFillColor(sf::Color::Blue);

	m_collisionBoxCenter.setSize(sf::Vector2f(4, 4));
	m_collisionBoxCenter.setPosition(m_collisionBox.getGlobalBounds().left + m_collisionBox.getOrigin().x, m_collisionBox.getGlobalBounds().top + m_collisionBox.getOrigin().y);
	m_collisionBoxCenter.setFillColor(sf::Color::Yellow);

	m_sprite.setTextureRect(sf::IntRect(m_frameX, m_frameY, GameConstants::FRAME_WIDTH, GameConstants::FRAME_HEIGHT));
	
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setScale(GameConstants::SCALE, GameConstants::SCALE);
	m_sprite.setPosition(m_collisionBox.getGlobalBounds().left+m_collisionBox.getGlobalBounds().width/2, m_collisionBox.getGlobalBounds().top + m_collisionBox.getGlobalBounds().height / 2);

	m_velocity.x = 0;
	m_velocity.y = 0;
	m_speed = (float)1 / GameConstants::SPEED_DENOMINATOR;

	m_movingState = NOWHERE;

	m_testMovingUp = false;
	m_testMovingDown = false;
	m_testMovingLeft = false;
	m_testMovingRight = false;
}
void Pacman::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);

	if (GameConstants::IS_DEBUGGING)
	{
		target.draw(m_collisionBox, states);
		target.draw(m_collisionBoxCenter, states);
	}
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

void Pacman::moveRight()
{
	m_collisionBox.move(m_speed,0);
}

void Pacman::moveLeft()
{
	m_collisionBox.move(-m_speed,0);
}

void Pacman::moveUp()
{
	m_collisionBox.move(0,-m_speed);
}

void Pacman::moveDown()
{
	m_collisionBox.move(0,m_speed);
}

void Pacman::stop()
{
	m_velocity.x = 0;
	m_velocity.y = 0;
}

void Pacman::update(sf::Clock clock)
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

void Pacman::playAnimation(sf::Clock clock)
{
	float timeSinceLastFrame = clock.getElapsedTime().asMilliseconds() - m_lastFrameTime;
	if (timeSinceLastFrame > GameConstants::FRAME_DURATION)
	{

		m_lastFrameTime = clock.getElapsedTime().asMilliseconds();

		if (m_frameIndex == GameConstants::NUMBER_OF_FRAMES-1)
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

void Pacman::setFreePathState(directionStates freePathState)
{
	//m_freePathState = freePathState;
}

sf::RectangleShape Pacman::getCollisionBox()
{
	return m_collisionBox;
}
