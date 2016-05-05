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
	
	collisionBox.setPosition(GameConstants::SPAWNX, GameConstants::SPAWNY);
	//collisionBox.setOrigin(collisionBox.getGlobalBounds().width / 2, collisionBox.getGlobalBounds().height / 2);
	collisionBox.setFillColor(sf::Color::Blue);

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

}
void Pacman::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite, states);

	if (GameConstants::IS_DEBUGGING)
	{
		target.draw(collisionBox, states);
	}
}

void Pacman::changeDirection()
{	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			moveRight();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{

			moveLeft();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (m_testMovingUp)
			{
				velocity.x = 0;
				velocity.y = -speed;
				sprite.setRotation(270);
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			moveDown();
		}
}

void Pacman::moveRight()
{
	if (m_testMovingRight)
	{
		velocity.x = speed;
		velocity.y = 0;
		sprite.setRotation(0);
	}
}

void Pacman::moveLeft()
{
	if (m_testMovingLeft)
	{
		velocity.x = -speed;
		velocity.y = 0;
		sprite.setRotation(180);
	}
}

void Pacman::moveUp()
{

}

void Pacman::moveDown()
{
	if (m_testMovingDown)
	{
		velocity.x = 0;
		velocity.y = speed;
		sprite.setRotation(90);
	}
}

void Pacman::stop()
{
	velocity.x = 0;
	velocity.y = 0;
}

void Pacman::update(sf::Clock clock)
{
	collisionBox.move(velocity);
	sprite.setPosition(collisionBox.getGlobalBounds().left + collisionBox.getGlobalBounds().width / 2, collisionBox.getGlobalBounds().top + collisionBox.getGlobalBounds().height / 2);

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

void Pacman::setIsMoving(bool isMoving)
{
	
}

sf::Rect<float> Pacman::getCollisionBox()
{
	return collisionBox.getGlobalBounds();
}
