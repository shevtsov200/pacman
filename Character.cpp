#include "Character.h"
#include <iostream>
#include <cmath>
Character::Character()
{

	m_spriteSheet.loadFromFile("resources/spriteSheetTransparent.png");

	m_sprite.setTexture(m_spriteSheet);

	m_lastFrameTime = 0;

	m_currentTile.setSize(sf::Vector2f(sf::Vector2f(GameConstants::TILE_SIZE, GameConstants::TILE_SIZE)));
	m_currentTile.setPosition(m_tilePosition.y*GameConstants::TILE_SIZE, m_tilePosition.x*GameConstants::TILE_SIZE);
	m_currentTile.setFillColor(sf::Color::White);

	m_velocity.x = 0;
	m_velocity.y = 0;
	m_speed = 0;

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
	target.draw(m_targetRectangle, states);
}

void Character::changeDirection()
{
}

void Character::moveRight()
{
	move(m_speed, 0);
}

void Character::moveLeft()
{
	move(-m_speed, 0);
}

void Character::moveUp()
{
	move(0, -m_speed);
}

void Character::moveDown()
{
	move(0, m_speed);
}
void Character::stop()
{
	m_movingState = NOWHERE;
}

void Character::move(float dx, float dy)
{
	sf::Vector2f pixelPosition;
	pixelPosition.x = getPixelPosition().x + dx;
	pixelPosition.y = getPixelPosition().y + dy;
	setPixelPosition(pixelPosition.x, pixelPosition.y);
	sf::Vector2i tilePosition = pixelsToIndexes(m_pixelPosition, sf::Vector2f(dx, dy));
	setTilePosition(tilePosition);	
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
void Character::checkWallCollisions(IntMatrix &map, int dim1, int dim2)
{
	int i = m_tilePosition.y;
	int j = m_tilePosition.x;

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
}

sf::Vector2i Character::pixelsToIndexes(sf::Vector2f position, sf::Vector2f dr)
{
	sf::Vector2i tilePosition;
	tilePosition.x = pixelToIndex(position.x, dr.x);
	tilePosition.y = pixelToIndex(position.y, dr.y);
	if (tilePosition.x == -1)
	{
		tilePosition.x = m_tilePosition.x;
	}
	if (tilePosition.y == -1)
	{
		tilePosition.y = m_tilePosition.y;
	}
	return tilePosition;
}
sf::Vector2f Character::tileToPixels(sf::Vector2i tilePosition)
{
	sf::Vector2f pixelPosition;
	pixelPosition.x = tilePosition.x*GameConstants::TILE_SIZE;
	pixelPosition.y = tilePosition.y*GameConstants::TILE_SIZE;
	return pixelPosition;
}

int Character::pixelToIndex(float x, float dx)
{
	int i;

	float tmp = x / GameConstants::TILE_SIZE;
	float floorX = floor(tmp);
	float ceilX = ceil(tmp);

	if (((tmp >= floorX) && (tmp < ceilX)) || (floorX == ceilX))
	{
		if (dx > 0)
		{
			i = floorX;
		}
		else if(dx < 0)
		{
			i = floorX + 1;
		}
		else
		{
			return -1;
		}
	}
	if (i < 0)
	{
		i = 0;
	}
	return i;
}

sf::Vector2f Character::getPixelPosition() const
{
	return m_pixelPosition;
}
sf::RectangleShape Character::getCollisionBox() const
{
	return m_collisionBox;
}

sf::RectangleShape Character::getCurrentTile() const
{
	return m_currentTile;
}

sf::Vector2i Character::getTilePosition() const
{
	return m_tilePosition;
}

Character::directionStates Character::getMovingState() const
{
	return m_movingState;
}

bool Character::getTestMovingUp() const
{
	return m_testMovingUp;
}

bool Character::getTestMovingLeft() const
{
	return m_testMovingLeft;
}

bool Character::getTestMovingDown() const
{
	return m_testMovingDown;
}

bool Character::getTestMovingRight() const
{
	return m_testMovingRight;
}

float Character::getSpeed() const
{
	return m_speed;
}

bool Character::getTestMoving(int direction) const
{
	if (direction == UP)
	{
		return getTestMovingUp();
	}
	else if (direction == LEFT)
	{
		return getTestMovingLeft();
	}
	else if (direction == DOWN)
	{
		return getTestMovingDown();
	}
	else if (direction == RIGHT)
	{

		return getTestMovingRight();
	}
}

void Character::setPixelPosition(float x, float y)
{
	m_pixelPosition.x = x;
	m_pixelPosition.y = y;
	m_collisionBox.setPosition(m_pixelPosition.x + m_collisionBox.getOrigin().x, m_pixelPosition.y + m_collisionBox.getOrigin().y);
	
	
}

void Character::updateCurrentTilePosition()
{
	m_currentTile.setPosition(m_tilePosition.x*GameConstants::TILE_SIZE, m_tilePosition.y*GameConstants::TILE_SIZE);
}

void Character::setInitialPosition()
{
	setTilePosition(m_spawnPosition);
	sf::Vector2f pixelPosition = tileToPixels(m_spawnPosition);
	setPixelPosition(pixelPosition.x, pixelPosition.y);
	
	m_lastTilePosition.x = 0;
	m_lastTilePosition.y = 0;

	m_checkTile.x = 0;
	m_checkTile.y = 0;
	
}

void Character::setTilePosition(sf::Vector2i tilePosition)
{
	/*if (tilePosition != m_tilePosition)
	{
		m_lastTilePosition = m_tilePosition;
	}*/
	m_tilePosition = tilePosition;
	updateCurrentTilePosition();
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

