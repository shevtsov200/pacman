#pragma once
#include <SFML\Graphics.hpp>
#include "GameConstants.h"
#include "Maze.h"
class Character : public sf::Drawable, public sf::Transformable
{
public:
	enum directionStates {UP, LEFT, DOWN, RIGHT, NOWHERE};

	Character();
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;

	void move(float dx, float dy);
	void moveUp();
	void moveLeft();
	void moveDown();
	void moveRight();
	void stop();

	virtual void update(sf::Clock clock);
	
	void hide();
	void makeVisible();
	void checkWallCollisions(IntMatrix &map, int dim1, int dim2);
	static int pixelToIndex(float x, float dx);
	sf::Vector2i pixelsToIndexes(sf::Vector2f position, sf::Vector2f dr);
	static sf::Vector2f tileToPixels(sf::Vector2i tilePosition);
	
	sf::RectangleShape getCollisionBox() const;
	sf::RectangleShape getCurrentTile() const;

	directionStates getMovingState() const;
	bool getTestMovingUp() const;
	bool getTestMovingLeft() const;
	bool getTestMovingDown() const;
	bool getTestMovingRight()const;
	float getSpeed()const;
	bool getTestMoving(int direction)const;
		
	sf::Vector2f getPixelPosition()const;
	sf::Vector2i getTilePosition()const;
	void setTexture(sf::Texture & spriteSheet);
	void setPixelPosition(float x, float y);
	void setTilePosition(sf::Vector2i tilePosition);
	void updateCurrentTilePosition();
	void setInitialPosition();
	void setInitialPosition(sf::Vector2i position);
	

	void setMovingState(directionStates directionState);
	void setIsUpFree(bool isValidPath);
	void setIsLeftFree(bool isValidPath);
	void setIsDownFree(bool isValidPath);
	void setIsRightFree(bool isValidPath);

protected:

	directionStates m_movingState;

	bool m_isUpFree, m_isDownFree, m_isRightFree, m_isLeftFree, m_isVisible;
	sf::RectangleShape m_currentTile;
	sf::Vector2i m_tilePosition, m_lastTilePosition, m_checkTile, m_spawnPosition;
	sf::Vector2f m_pixelPosition;
	sf::Sprite m_sprite;
	sf::Texture m_spriteSheet;

	sf::RectangleShape m_collisionBox;
	float m_speed, m_lastFrameTime;
	int m_frameX, m_frameY, m_frameIndex;



};