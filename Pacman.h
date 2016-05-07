#pragma once
#include <SFML\Graphics.hpp>
#include "GameConstants.h"

class Pacman : public sf::Drawable, public sf::Transformable
{
public: 
	Pacman();
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void changeDirection();
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
	void stop();
	void update(sf::Clock clock);
	void playAnimation(sf::Clock clock);
	void setIsMoving(bool isMoving);
	sf::Rect<float> getCollisionBox();

	//!!!!!!
	bool m_testMovingUp; 
	bool m_testMovingDown;
	bool m_testMovingLeft;
	bool m_testMovingRight;
	//!!!!!!!
	bool m_isMovingRight;
	bool m_isMovingLeft;
	bool m_isMovingUp;
	bool m_isMovingDown;

private:
	

	sf::Sprite sprite;
	sf::Texture spriteSheet;

	sf::Vector2f velocity;

	sf::RectangleShape collisionBox;
	float speed;
	

	float lastFrameTime;
	int frameX;
	int frameY;
	int frameIndex;

};
