#include "Pacman.h"

Pacman::Pacman()
{
	spriteSheet.loadFromFile("spriteSheet.png");

	sprite.setTexture(spriteSheet);
	sprite.setTextureRect(sf::IntRect(473, 0, 15, 15));
	sprite.setPosition(50, 50);
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);

	velocity.x = 0;
	velocity.y = 0;
}
void Pacman::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

void Pacman::changeDirection(sf::Event event)
{
	float speed = 0.05;
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

void Pacman::update()
{
	sprite.move(velocity);
}
