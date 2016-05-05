#include "Pacman.h"

Pacman::Pacman(Maze *maze)
{
	m_maze = maze;

	frameWidth = m_maze->getSheetTileSize() * 2;
	frameHeight = frameWidth;
	frameOffsetX = m_maze->getSheetTileSize() * 56;

	tileSize = m_maze->getTileSize();
	scale = m_maze->getScale();
	isDebugging = m_maze->getIsDebugging();
	spriteWidth = tileSize;
	spriteHeight = spriteWidth;
	spawnX = tileSize *14;
	spawnY = tileSize * 23;

	frameIndex = 0;
	frameX = frameOffsetX;
	frameY = 0;

	lastFrameTime = 0;


	spriteSheet.loadFromFile("resources/spriteSheet3.png");
	sprite.setTexture(spriteSheet);

	collisionBox.setSize(sf::Vector2f(tileSize, tileSize));
	
	collisionBox.setPosition(spawnX, spawnY);
	//collisionBox.setOrigin(collisionBox.getGlobalBounds().width / 2, collisionBox.getGlobalBounds().height / 2);
	collisionBox.setFillColor(sf::Color::Blue);

	sprite.setTextureRect(sf::IntRect(frameX, frameY, frameWidth, frameHeight));
	
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	sprite.setScale(scale, scale);
	sprite.setPosition(collisionBox.getGlobalBounds().left+collisionBox.getGlobalBounds().width/2, collisionBox.getGlobalBounds().top + collisionBox.getGlobalBounds().height / 2);

	velocity.x = 0;
	velocity.y = 0;
	speed = (float)1 / SPEED_DENOMINATOR;

	m_isMoving = true;
}
void Pacman::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite, states);

	if (isDebugging)
	{
		target.draw(collisionBox, states);
	}
}

void Pacman::changeDirection()
{
	if (m_isMoving)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			velocity.x = speed;
			velocity.y = 0;
			sprite.setRotation(0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			velocity.x = -speed;
			velocity.y = 0;
			sprite.setRotation(180);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			velocity.x = 0;
			velocity.y = -speed;
			sprite.setRotation(270);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			velocity.x = 0;
			velocity.y = speed;
			sprite.setRotation(90);
		}
	}
	else
	{
		velocity.x = 0;
		velocity.y = 0;
	}
}

void Pacman::moveRight()
{
	velocity.x = speed;
	velocity.y = 0;
	sprite.setRotation(0);
}

void Pacman::moveLeft()
{
	velocity.x = -speed;
	velocity.y = 0;
	sprite.setRotation(180);
}

void Pacman::moveUp()
{
	velocity.x = 0;
	velocity.y = -speed;
	sprite.setRotation(270);
}

void Pacman::moveDown()
{
	velocity.x = 0;
	velocity.y = speed;
	sprite.setRotation(90);
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
	if (timeSinceLastFrame > FRAME_DURATION)
	{

		lastFrameTime = clock.getElapsedTime().asMilliseconds();

		if (frameIndex == NUMBER_OF_FRAMES-1)
		{
			frameIndex = 0;
		}
		else
		{
			frameIndex++;
		}
		frameX = frameOffsetX+frameWidth*frameIndex;
		sprite.setTextureRect(sf::IntRect(frameX, frameY, frameWidth, frameHeight));		
	}
}

void Pacman::setIsMoving(bool isMoving)
{
	m_isMoving = isMoving;
}

sf::Rect<float> Pacman::getCollisionBox()
{
	return collisionBox.getGlobalBounds();
}
