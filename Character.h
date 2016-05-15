#pragma once
#include <SFML\Graphics.hpp>
#include "GameConstants.h"
class Character : public sf::Drawable, public sf::Transformable
{
public:
	enum directionStates { RIGHT, LEFT, UP, DOWN, NOWHERE };

	Character();
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void changeDirection();
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
	void stop();
	void update(sf::Clock clock);
	void playAnimation(sf::Clock clock);
	void hide();
	void checkWallCollisions(sf::RectangleShape *walls, int dim1, int dim2);
	int pixelsToIndex(float x);
	sf::Vector2f getPosition();
	sf::RectangleShape getCollisionBox();
	sf::RectangleShape getCurrentTile();
	int getCharacterI();
	int getCharacterJ();
	directionStates getMovingState();
	bool getTestMovingUp();
	bool getTestMovingLeft();
	bool getTestMovingDown();
	bool getTestMovingRight();
	float getSpeed();

	void setPosition(float x, float y);
	void setCurrentTilePosition(float x, float y);
	void setCharacterI(int characterI);
	void setCharacterJ(int characterJ);
	void setMovingState(directionStates directionState);
	void setTestMovingUp(bool isValidPath);
	void setTestMovingLeft(bool isValidPath);
	void setTestMovingDown(bool isValidPath);
	void setTestMovingRight(bool isValidPath);


protected:

	//!!!!!!!!
	directionStates m_movingState;

	bool m_testMovingUp;
	bool m_testMovingDown;
	bool m_testMovingRight;
	bool m_testMovingLeft;
	//!!!!!!!!

	sf::RectangleShape m_currentTile;
	int m_characterI, m_characterJ;

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