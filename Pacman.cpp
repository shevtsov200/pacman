#include "Pacman.h"

Pacman::Pacman()
{
	spriteSheet.loadFromFile("spriteSheet.png");

	sprite.setTexture(spriteSheet);

	frameIndex = 0;
	frameX = 2;
	frameY = 2;

	lastFrameTime = 0;

	sprite.setTextureRect(sf::IntRect(frameX, frameY, frameWidth, frameHeight));
	sprite.setPosition(50, 50);
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);

	velocity.x = 0;
	velocity.y = 0;
}
void Pacman::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

void Pacman::changeDirection()
{
	float speed = 0.03f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		velocity.x = speed;
		velocity.y = 0;
		sprite.setRotation(180);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		velocity.x = -speed;
		velocity.y = 0;
		sprite.setRotation(0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		velocity.x = 0;
		velocity.y = -speed;
		sprite.setRotation(90);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		velocity.x = 0;
		velocity.y = speed;
		sprite.setRotation(270);
	}
}

void Pacman::update(sf::Clock clock)
{
	sprite.move(velocity);
	playAnimation(clock);
}

void Pacman::playAnimation(sf::Clock clock)
{
	float timeSinceLastFrame = clock.getElapsedTime().asMilliseconds() - lastFrameTime;
	if (timeSinceLastFrame > frameDuration)
	{

		lastFrameTime = clock.getElapsedTime().asMilliseconds();

		if (frameIndex == numberOfFrames-1)
		{
			frameIndex = 0;
		}
		else
		{
			frameIndex++;
		}
		frameX = frameOffsetX + frameWidth*frameIndex + frameOffsetX*frameIndex;
		sprite.setTextureRect(sf::IntRect(frameX, frameY, frameWidth, frameHeight));
		
	}
}
