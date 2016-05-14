#pragma once
#include <SFML\Graphics.hpp>
#include "GameConstants.h"
#include "Character.h"

class Pacman : public Character
{
public: 
	enum directionStates { RIGHT, LEFT, UP, DOWN, NOWHERE};

	Pacman();
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void changeDirection();
	void update(sf::Clock clock);
	void playAnimation(sf::Clock clock);
	sf::RectangleShape getCollisionBox();

	//!!!!!!!!
	directionStates m_movingState;

	bool m_testMovingUp;
	bool m_testMovingDown;
	bool m_testMovingRight;
	bool m_testMovingLeft;
	//!!!!!!!!

private:
	

	/*sf::Sprite m_sprite;
	sf::Texture m_spriteSheet;

	sf::Vector2f m_velocity;

	sf::RectangleShape m_collisionBox;
	sf::RectangleShape m_collisionBoxCenter;
	float m_speed;
	

	float m_lastFrameTime;
	int m_frameX;
	int m_frameY;
	int m_frameIndex;*/

};
