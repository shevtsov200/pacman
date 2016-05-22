#include "Character.h"
#include <iostream>
#include <cmath>
Character::Character()
{

	m_spriteSheet.loadFromFile("resources/spriteSheet3.png");

	m_sprite.setTexture(m_spriteSheet);

	m_lastFrameTime = 0;

	m_currentTile.setSize(sf::Vector2f(sf::Vector2f(GameConstants::TILE_SIZE, GameConstants::TILE_SIZE)));
	m_currentTile.setPosition(m_tilePosition.y*GameConstants::TILE_SIZE, m_tilePosition.x*GameConstants::TILE_SIZE);
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
	//setCurrentPosition()
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
	m_movingState = NOWHERE;
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

	//setCurrentTilePosition(GameConstants::TILE_SIZE*m_characterJ, GameConstants::TILE_SIZE*m_characterI);

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
void Character::checkWallCollisions(IntMatrix &map, int dim1, int dim2)
{

	/*m_tilePosition = pixelsToIndexes(sf::Vector2f(getCollisionBox().getGlobalBounds().left + getCollisionBox().getOrigin().x,
		getCollisionBox().getGlobalBounds().top + getCollisionBox().getOrigin().y));*/

	int i = m_tilePosition.x;
	int j = m_tilePosition.y;

	if (i > 0)
	{
		m_testMovingUp = (map[i - 1][j] != Maze::WALL);
	}
	if (j > 0)
	{
		m_testMovingLeft = (map[i][j - 1] != Maze::WALL);
	}
	if (i < GameConstants::MAZE_HEIGHT)
	{
		m_testMovingDown = (map[i + 1][j] != Maze::WALL);
	}
	if (j < GameConstants::MAZE_WIDTH)
	{
		m_testMovingRight = (map[i][j + 1] != Maze::WALL);
	}

	//setCurrentTilePosition(GameConstants::TILE_SIZE*m_characterJ, GameConstants::TILE_SIZE*m_characterI);
}

int Character::xToJ(float x)
{
	float tmp = x / GameConstants::TILE_SIZE;
	float tmp2;
	if (modf(tmp, &tmp2) == 0)
	{
		return tmp;
	}
	else
	{
		return m_tilePosition.y;
	}
}

int Character::yToI(float y)
{
	float tmp = y / GameConstants::TILE_SIZE;
	float tmp2;
	if (modf(tmp, &tmp2) == 0)
	{
		return tmp;
	}
	else
	{
		return m_tilePosition.x;
	}
}

sf::Vector2i Character::pixelsToIndexes(sf::Vector2f position)
{
	sf::Vector2i tmp;
	tmp.x = yToI(position.x);
	tmp.y = xToJ(position.y);

	return tmp;
	/*float x = position.x;
	float y = position.y;
	float tmpI = y / GameConstants::TILE_SIZE;
	float tmpIInt;
	if (modf(tmpI, &tmpIInt) == 0)
	{
		return tmpI;
	}
	else
	{
		return m_characterI;
	}*/
}

sf::Vector2f Character::getPixelPosition()
{
	return sf::Vector2f(m_collisionBox.getGlobalBounds().left, m_collisionBox.getGlobalBounds().top);
}
sf::RectangleShape Character::getCollisionBox()
{
	return m_collisionBox;
}

sf::RectangleShape Character::getCurrentTile()
{
	return m_currentTile;
}

/*int Character::getCharacterI()
{
	return m_ti;
}

int Character::getCharacterJ()
{
	return m_characterJ;
}*/

sf::Vector2i Character::getTilePosition()
{
	return m_tilePosition;
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

void Character::setCurrentPosition(float x, float y)
{
	m_collisionBox.setPosition(x+m_collisionBox.getOrigin().x, y + m_collisionBox.getOrigin().y);
	//m_tilePosition = pixelsToIndexes(sf::Vector2f(x + m_collisionBox.getOrigin().x, y + m_collisionBox.getOrigin().y));
	//m_characterI = pixelsToIndex(m_collisionBox.getGlobalBounds().top + m_collisionBox.getOrigin().y);
	//m_characterJ = pixelsToIndex(m_collisionBox.getGlobalBounds().left+ m_collisionBox.getOrigin().x);
}

void Character::setCurrentTilePosition(float x, float y)
{
	m_currentTile.setPosition(x, y);
}

/*void Character::setCharacterI(int characterI)
{
	m_characterI = characterI;
}

void Character::setCharacterJ(int characterJ)
{
	m_characterJ = characterJ;
}*/

void Character::setInitialPosition(sf::Vector2i initialPosition)
{
	m_tilePosition = initialPosition;
	setCurrentPosition(m_tilePosition.y*GameConstants::TILE_SIZE, m_tilePosition.x*GameConstants::TILE_SIZE);
	m_lastTilePosition = m_tilePosition;
	
}

void Character::setTilePosition(sf::Vector2i tilePosition)
{
	m_tilePosition = tilePosition;
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

