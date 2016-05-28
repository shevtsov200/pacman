#pragma once
#include <SFML\Graphics.hpp>
#include "Character.h"
class Enemy : public Character
{
public:
	Enemy();
	void changeDirection();
	void changeHorizontalDirection();
	void changeVerticalDirection();
	void update();
	void updateSprite();

	virtual void setTarget(sf::Vector2i target);

	sf::Vector2i getTarget();
protected:
	sf::Vector2i m_target;	
	int m_frameOffsetY;
};
