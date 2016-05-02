#include "Pacman.h"

Pacman::Pacman()
{
	spriteSheet.loadFromFile("resources/spriteSheet3.png");

	sprite.setTexture(spriteSheet);

	frameIndex = 0;
	frameX = FRAME_OFFSETX;
	frameY = 0;

	lastFrameTime = 0;

	collisionBox.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	collisionBox.setPosition(SPAWNX, SPAWNY);
	collisionBox.setOrigin(collisionBox.getGlobalBounds().width / 2, collisionBox.getGlobalBounds().height / 2);

	sprite.setTextureRect(sf::IntRect(frameX, frameY, FRAME_WIDTH, FRAME_HEIGHT));
	
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	sprite.setScale(SCALE, SCALE);
	sprite.setPosition(collisionBox.getGlobalBounds().left+collisionBox.getGlobalBounds().width/2, collisionBox.getGlobalBounds().top + collisionBox.getGlobalBounds().height / 2);

	velocity.x = 0;
	velocity.y = 0;
}
void Pacman::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite, states);

	if (IS_DEBUGGING)
	{
		target.draw(collisionBox, states);
	}
}

void Pacman::changeDirection()
{
	float speed = (float) 1 / SPEED_DENOMINATOR;
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
		frameX = FRAME_OFFSETX+FRAME_WIDTH*frameIndex;
		sprite.setTextureRect(sf::IntRect(frameX, frameY, FRAME_WIDTH, FRAME_HEIGHT));		
	}
}

sf::Rect<float> Pacman::getCollisionBox()
{
	return collisionBox.getGlobalBounds();
}
