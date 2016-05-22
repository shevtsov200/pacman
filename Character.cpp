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
		//target.draw(m_currentTile, states);
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
	//m_collisionBox.move(m_speed, 0);
	move(m_speed, 0);
}

void Character::moveLeft()
{
	//m_collisionBox.move(-m_speed, 0);
	move(-m_speed, 0);
}

void Character::moveUp()
{
	//m_collisionBox.move(0, -m_speed);
	move(0, -m_speed);
}

void Character::moveDown()
{
	//m_collisionBox.move(0, m_speed);
	move(0, m_speed);
}
void Character::stop()
{
	m_movingState = NOWHERE;
}

void Character::move(float dx, float dy)
{
	setPixelPosition(getPixelPosition().x + dx, getPixelPosition().y + dy);

	//setCurrentPosition(getPixelPosition().x + dx, getPixelPosition().y + dy);
	//setTilePosition(pixelsToIndexes(m_pixelPosition));


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

	//setCurrentTilePosition(GameConstants::TILE_SIZE*m_characterJ, GameConstants::TILE_SIZE*m_characterI);
}

int Character::pixelToTileX(float x)
{
	float tmp = x / GameConstants::TILE_SIZE;
	float tmp3 = floor(x / GameConstants::TILE_SIZE);
	float tmp2;
	if (modf(tmp, &tmp2) == 0)
	{
		return tmp;
	}
	else if (tmp3 != m_tilePosition.x)
	{
		return tmp3;
	}
	else
	{
		return m_tilePosition.x;
	}
}

int Character::pixelToTileY(float y)
{
	float tmp = y / GameConstants::TILE_SIZE;
	float tmp3 = floor(y / GameConstants::TILE_SIZE);
	float tmp2;
	if (modf(tmp, &tmp2) == 0)
	{
		return tmp;
	}
	else if (tmp3 != m_tilePosition.y)
	{
		return tmp3;
	}
	else
	{
		return m_tilePosition.y;
	}
}

sf::Vector2i Character::pixelsToIndexes(sf::Vector2f position)
{
	sf::Vector2i tmp;



	tmp.x = pixelToTileX(position.x);
	tmp.y = pixelToTileY(position.y);

	return tmp;
}

sf::Vector2f Character::getPixelPosition()
{
	//return sf::Vector2f(m_collisionBox.getGlobalBounds().left, m_collisionBox.getGlobalBounds().top);
	return m_pixelPosition;
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

bool Character::getTestMoving(int direction)
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
	m_lastTilePosition = m_tilePosition;
	sf::Vector2i tilePosition = pixelsToIndexes(m_pixelPosition);
	setTilePosition(tilePosition);
	
	//m_collisionBox.setPosition(x+m_collisionBox.getOrigin().x, y + m_collisionBox.getOrigin().y);

	//m_pixelPosition.x = m_collisionBox.getPosition().x;
	//m_pixelPosition.y = m_collisionBox.getPosition().y;
}

void Character::updateCurrentTilePosition()
{
	m_currentTile.setPosition(m_tilePosition.x*GameConstants::TILE_SIZE, m_tilePosition.y*GameConstants::TILE_SIZE);
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
	setTilePosition(initialPosition);
	setPixelPosition(m_tilePosition.x*GameConstants::TILE_SIZE, m_tilePosition.y*GameConstants::TILE_SIZE);
	//m_lastTilePosition = m_tilePosition;
	m_lastTilePosition.x = 0;
	m_lastTilePosition.y = 0;
	/*m_tilePosition = initialPosition;
	setCurrentPosition(m_tilePosition.y*GameConstants::TILE_SIZE, m_tilePosition.x*GameConstants::TILE_SIZE);
	m_lastTilePosition = m_tilePosition;*/
	
}

void Character::setTilePosition(sf::Vector2i tilePosition)
{
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

