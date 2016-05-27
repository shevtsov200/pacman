#pragma once
#include <SFML\Graphics.hpp>
#include "GameConstants.h"
#include "Maze.h"
#include "CharacterPosition.h"
class Character : public sf::Drawable, public sf::Transformable
{
public:
	//enum directionStates { RIGHT, LEFT, UP, DOWN, NOWHERE };
	enum directionStates {UP, LEFT, DOWN, RIGHT, NOWHERE};

	Character();
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void changeDirection();

	void move(float dx, float dy);
	void moveUp();
	void moveLeft();
	void moveDown();
	void moveRight();
	void stop();

	void update(sf::Clock clock);
	void playAnimation(sf::Clock clock);
	void hide();
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
	sf::Vector2i getTilePosition()const;\
	void setPixelPosition(float x, float y);
	void setTilePosition(sf::Vector2i tilePosition);
	void updateCurrentTilePosition();
	void setInitialPosition(sf::Vector2i initialPosition);
	

	void setMovingState(directionStates directionState);
	void setTestMovingUp(bool isValidPath);
	void setTestMovingLeft(bool isValidPath);
	void setTestMovingDown(bool isValidPath);
	void setTestMovingRight(bool isValidPath);


protected:

	//!!!!!!!!
	//CharacterPosition m_currentPosition;

	directionStates m_movingState, m_oldMovingState;

	bool m_testMovingUp;
	bool m_testMovingDown;
	bool m_testMovingRight;
	bool m_testMovingLeft;
	//!!!!!!!!

	sf::RectangleShape m_currentTile;
	//int m_characterI, m_characterJ;
	sf::Vector2i m_tilePosition, m_lastTilePosition;
	sf::Vector2f m_pixelPosition;
	sf::Sprite m_sprite;
	sf::Texture m_spriteSheet;

	sf::Vector2f m_velocity;

	sf::RectangleShape m_collisionBox;
	sf::RectangleShape m_collisionBoxCenter;
	float m_speed;


	float m_lastFrameTime;
	int m_frameX;
	int m_frameY;
	int m_frameIndex;

	bool m_isVisible;

};