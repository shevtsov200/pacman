#include "Character.h"
#include <iostream>
Character::Character()
{

	m_spriteSheet.loadFromFile("resources/spriteSheet3.png");

	m_sprite.setTexture(m_spriteSheet);

	m_lastFrameTime = 0;

	m_currentTile.setSize(sf::Vector2f(sf::Vector2f(GameConstants::TILE_SIZE, GameConstants::TILE_SIZE)));
	m_currentTile.setPosition(m_characterJ*GameConstants::TILE_SIZE, m_characterI*GameConstants::TILE_SIZE);
	m_currentTile.setFillColor(sf::Color::White);

	m_velocity.x = 0;
	m_velocity.y = 0;
	m_speed = (float)1 / GameConstants::SPEED_DENOMINATOR;

	m_movingState = RIGHT;

	m_testMovingUp = false;
	m_testMovingDown = false;
	m_testMovingLeft = false;
	m_testMovingRight = false;

	m_isVisible = true;
}

void Character::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (m_isVisible)
	{
		target.draw(m_sprite, states);
	}
	if (GameConstants::IS_DEBUGGING)
	{
		target.draw(m_collisionBox, states);
		target.draw(m_collisionBoxCenter, states);
		target.draw(m_currentTile, states);
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
void Character::hide()
{
	m_isVisible = false;
}
void Character::checkWallCollisions(sf::RectangleShape * walls, int dim1, int dim2)
{
	int characterJ = pixelsToIndex(getCollisionBox().getGlobalBounds().left + getCollisionBox().getOrigin().x);
	setCharacterJ(characterJ);

	int characterI = pixelsToIndex(getCollisionBox().getGlobalBounds().top + getCollisionBox().getOrigin().y);
	setCharacterI(characterI);

	float width = walls[dim2*characterI + (characterJ + 1)].getGlobalBounds().width;
	float height = walls[dim2*characterI + (characterJ + 1)].getGlobalBounds().height;
	float x = walls[dim2*characterI + (characterJ + 1)].getGlobalBounds().left;
	float y = walls[dim2*characterI + (characterJ + 1)].getGlobalBounds().top;


	bool testMovingUp = !getCollisionBox().getGlobalBounds().intersects(walls[dim2*(characterI - 1) + characterJ].getGlobalBounds());
	bool testMovingDown = !getCollisionBox().getGlobalBounds().intersects(walls[dim2*(characterI + 1) + characterJ].getGlobalBounds());
	bool testMovingLeft = !getCollisionBox().getGlobalBounds().intersects(walls[dim2*characterI + (characterJ - 1)].getGlobalBounds());
	bool testMovingRight = !getCollisionBox().getGlobalBounds().intersects(walls[dim2*characterI + (characterJ + 1)].getGlobalBounds());

	setTestMovingUp(testMovingUp);
	setTestMovingLeft(testMovingLeft);
	setTestMovingDown(testMovingDown);
	setTestMovingRight(testMovingRight);

	setCurrentTilePosition(GameConstants::TILE_SIZE*characterJ, GameConstants::TILE_SIZE*characterI);
}
int Character::pixelsToIndex(float x)
{
	return x / GameConstants::TILE_SIZE;
}
sf::Vector2f Character::getPosition()
{
	return sf::Vector2f(m_collisionBox.getGlobalBounds().left, m_collisionBox.getGlobalBounds().top);
}
sf::RectangleShape Character::getCollisionBox()
{
	return m_collisionBox;
}

int Character::getCharacterI()
{
	return m_characterI;
}

int Character::getCharacterJ()
{
	return m_characterJ;
}

Character::directionStates Character::getMovingState()
{
	return m_movingState;
}

bool Character::getTestMovingUp()
{
	return m_testMovingUp;
}

bool Character::getTestMovingLeft()
{
	return m_testMovingLeft;
}

bool Character::getTestMovingDown()
{
	return m_testMovingDown;
}

bool Character::getTestMovingRight()
{
	return m_testMovingRight;
}

float Character::getSpeed()
{
	return m_speed;
}

void Character::setPosition(float x, float y)
{
	m_collisionBox.setPosition(x, y);
}

void Character::setCurrentTilePosition(float x, float y)
{
	m_currentTile.setPosition(x, y);
}

void Character::setCharacterI(int characterI)
{
	m_characterI = characterI;
}

void Character::setCharacterJ(int characterJ)
{
	m_characterJ = characterJ;
}

void Character::setMovingState(directionStates directionState)
{
	m_movingState = directionState;
}

void Character::setTestMovingUp(bool isValidPath)
{
	m_testMovingUp = isValidPath;
}

void Character::setTestMovingLeft(bool isValidPath)
{
	m_testMovingLeft = isValidPath;
}

void Character::setTestMovingDown(bool isValidPath)
{
	m_testMovingDown = isValidPath;
}

void Character::setTestMovingRight(bool isValidPath)
{
	m_testMovingRight = isValidPath;
}

