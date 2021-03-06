#include "Character.h"
#include <iostream>
#include <cmath>
Character::Character()
{
	m_lastFrameTime = 0;
	m_speed = 0;

	m_movingState = RIGHT;
	m_isUpFree = false;
	m_isDownFree = false;
	m_isLeftFree = false;
	m_isRightFree = false;
	m_isVisible = true;
}

void Character::setTexture(sf::Texture & spriteSheet)
{
	m_spriteSheet.loadFromFile("resources/spriteSheetTransparent.png");

	m_sprite.setTexture(m_spriteSheet);
}

void Character::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (m_isVisible)
	{
		target.draw(m_sprite, states);
	}
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
	if (m_movingState == UP && m_isUpFree)
	{
		moveUp();
	}
	if (m_movingState == DOWN && m_isDownFree)
	{
		moveDown();
	}
	if (m_movingState == RIGHT && m_isRightFree)
	{
		moveRight();
	}
	if (m_movingState == LEFT && m_isLeftFree)
	{
		moveLeft();
	}

	m_sprite.setPosition(m_collisionBox.getGlobalBounds().left + m_collisionBox.getGlobalBounds().width / 2, m_collisionBox.getGlobalBounds().top + m_collisionBox.getGlobalBounds().height / 2);
}

void Character::hide()
{
	m_isVisible = false;
}
void Character::makeVisible()
{
	m_isVisible = true;
}
void Character::checkWallCollisions(IntMatrix &map, int dim1, int dim2)
{
	// ��������� �� ����� �� � ������ �����������
	int i = m_tilePosition.y;
	int j = m_tilePosition.x;

	if (i < 0)
	{
		i = 1;
	}
	else if (i > GameConstants::MAZE_HEIGHT)
	{
		i = GameConstants::MAZE_HEIGHT - 1;
	}
	if (j < 0)
	{
		j = 1;
	}
	else if (j > GameConstants::MAZE_WIDTH)
	{
		j = GameConstants::MAZE_WIDTH -1;
	}

	m_isUpFree = (map[i - 1][j] != Maze::WALL);
	m_isLeftFree = (map[i][j - 1] != Maze::WALL);
	m_isDownFree = (map[i + 1][j] != Maze::WALL);
	m_isRightFree = (map[i][j + 1] != Maze::WALL);
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

sf::Vector2i Character::getTilePosition() const
{
	return m_tilePosition;
}

Character::directionStates Character::getMovingState() const
{
	return m_movingState;
}

bool Character::getIsUpFree() const
{
	return m_isUpFree;
}

bool Character::getIsLeftFree() const
{
	return m_isLeftFree;
}

bool Character::getIsDownFree() const
{
	return m_isDownFree;
}

bool Character::getIsRightFree() const
{
	return m_isRightFree;
}

float Character::getSpeed() const
{
	return m_speed;
}

bool Character::getIsFree(int direction) const
{
	if (direction == UP)
	{
		return getIsUpFree();
	}
	else if (direction == LEFT)
	{
		return getIsLeftFree();
	}
	else if (direction == DOWN)
	{
		return getIsDownFree();
	}
	else if (direction == RIGHT)
	{

		return getIsRightFree();
	}
}

void Character::setPixelPosition(float x, float y)
{
	m_pixelPosition.x = x;
	m_pixelPosition.y = y;
	m_collisionBox.setPosition(m_pixelPosition.x + m_collisionBox.getOrigin().x, m_pixelPosition.y + m_collisionBox.getOrigin().y);
	
	
}

void Character::setInitialPosition()
{
	setTilePosition(m_spawnPosition);
	sf::Vector2f pixelPosition = tileToPixels(m_spawnPosition);
	setPixelPosition(pixelPosition.x, pixelPosition.y);

	m_checkTile.x = 0;
	m_checkTile.y = 0;
	
}

void Character::setInitialPosition(sf::Vector2i position)
{
	setTilePosition(position);
	sf::Vector2f pixelPosition = tileToPixels(position);
	setPixelPosition(pixelPosition.x, pixelPosition.y);

	m_checkTile.x = 0;
	m_checkTile.y = 0;

}

void Character::setTilePosition(sf::Vector2i tilePosition)
{
	m_tilePosition = tilePosition;
}

void Character::setMovingState(directionStates directionState)
{
	m_movingState = directionState;
}

void Character::setIsUpFree(bool isValidPath)
{
	m_isUpFree = isValidPath;
}

void Character::setIsLeftFree(bool isValidPath)
{
	m_isLeftFree = isValidPath;
}

void Character::setIsDownFree(bool isValidPath)
{
	m_isDownFree = isValidPath;
}

void Character::setIsRightFree(bool isValidPath)
{
	m_isRightFree = isValidPath;
}

