#include "Pacman.h"

Pacman::Pacman()
{
	spriteSheet.loadFromFile("resources/spriteSheet3.png");

	sprite.setTexture(spriteSheet);

	frameIndex = 0;
	frameX = GameConstants::FRAME_OFFSETX;
	frameY = 0;

	lastFrameTime = 0;

	collisionBox.setSize(sf::Vector2f(GameConstants::TILE_SIZE, GameConstants::TILE_SIZE));
	
	collisionBox.setOrigin(collisionBox.getGlobalBounds().width / 2, collisionBox.getGlobalBounds().height / 2);
	collisionBox.setPosition(GameConstants::SPAWNX+collisionBox.getOrigin().x, GameConstants::SPAWNY + collisionBox.getOrigin().y);
	
	collisionBox.setFillColor(sf::Color::Blue);

	collisionBoxCenter.setSize(sf::Vector2f(4, 4));
	collisionBoxCenter.setPosition(collisionBox.getGlobalBounds().left + collisionBox.getOrigin().x, collisionBox.getGlobalBounds().top + collisionBox.getOrigin().y);
	collisionBoxCenter.setFillColor(sf::Color::Yellow);

	sprite.setTextureRect(sf::IntRect(frameX, frameY, GameConstants::FRAME_WIDTH, GameConstants::FRAME_HEIGHT));
	
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	sprite.setScale(GameConstants::SCALE, GameConstants::SCALE);
	sprite.setPosition(collisionBox.getGlobalBounds().left+collisionBox.getGlobalBounds().width/2, collisionBox.getGlobalBounds().top + collisionBox.getGlobalBounds().height / 2);

	velocity.x = 0;
	velocity.y = 0;
	speed = (float)1 / GameConstants::SPEED_DENOMINATOR;

	m_testMovingDown = true;
	m_testMovingLeft = true;
	m_testMovingRight = true;
	m_testMovingUp = true;

	m_isMovingRight = false;
	m_isMovingLeft = false;
	m_isMovingUp = false;
	m_isMovingDown = false;
}
void Pacman::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite, states);

	if (GameConstants::IS_DEBUGGING)
	{
		target.draw(collisionBox, states);
		target.draw(collisionBoxCenter, states);
	}
}

void Pacman::changeDirection()
{	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (m_testMovingRight)
			{
				m_isMovingRight = true;
				m_isMovingLeft = false;
				m_isMovingUp = false;
				m_isMovingDown = false;

				sprite.setRotation(0);
			}

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (m_testMovingLeft)
			{
				m_isMovingRight = false;
				m_isMovingLeft = true;
				m_isMovingUp = false;
				m_isMovingDown = false;

				sprite.setRotation(180);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (m_testMovingUp)
			{
				m_isMovingRight = false;
				m_isMovingLeft = false;
				m_isMovingUp = true;
				m_isMovingDown = false;

				sprite.setRotation(270);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (m_testMovingDown)
			{
				m_isMovingRight = false;
				m_isMovingLeft = false;
				m_isMovingUp = false;
				m_isMovingDown = true;

				sprite.setRotation(90);
			}
		}
}

void Pacman::moveRight()
{
	if (m_testMovingRight && m_isMovingRight)
	{
		collisionBox.move(speed,0);
	}
}

void Pacman::moveLeft()
{
	if (m_testMovingLeft && m_isMovingLeft)
	{
		collisionBox.move(-speed,0);
	}
}

void Pacman::moveUp()
{
	if (m_testMovingUp && m_isMovingUp)
	{
		collisionBox.move(0,-speed);
	}
}

void Pacman::moveDown()
{
	if (m_testMovingDown && m_isMovingDown)
	{
		collisionBox.move(0,speed);
	}
}

void Pacman::stop()
{
	velocity.x = 0;
	velocity.y = 0;
}

void Pacman::update(sf::Clock clock)
{
	if (m_testMovingUp && m_isMovingUp)
	{
		moveUp();
	}
	if (m_testMovingDown && m_isMovingDown)
	{
		moveDown();
	}
	if (m_testMovingRight && m_isMovingRight)
	{
		moveRight();
	}
	if (m_testMovingLeft && m_isMovingLeft)
	{
		moveLeft();
	}

	sprite.setPosition(collisionBox.getGlobalBounds().left + collisionBox.getGlobalBounds().width / 2, collisionBox.getGlobalBounds().top + collisionBox.getGlobalBounds().height / 2);

	collisionBoxCenter.setPosition(collisionBox.getGlobalBounds().left + collisionBox.getOrigin().x, collisionBox.getGlobalBounds().top + collisionBox.getOrigin().y);

	playAnimation(clock);
}

void Pacman::playAnimation(sf::Clock clock)
{
	float timeSinceLastFrame = clock.getElapsedTime().asMilliseconds() - lastFrameTime;
	if (timeSinceLastFrame > GameConstants::FRAME_DURATION)
	{

		lastFrameTime = clock.getElapsedTime().asMilliseconds();

		if (frameIndex == GameConstants::NUMBER_OF_FRAMES-1)
		{
			frameIndex = 0;
		}
		else
		{
			frameIndex++;
		}
		frameX = GameConstants::FRAME_OFFSETX + GameConstants::FRAME_WIDTH*frameIndex;
		sprite.setTextureRect(sf::IntRect(frameX, frameY, GameConstants::FRAME_WIDTH, GameConstants::FRAME_HEIGHT));
	}
}

sf::RectangleShape Pacman::getCollisionBox()
{
	return collisionBox;
}
