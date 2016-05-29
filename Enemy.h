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
	void setName(std::string name);

	virtual void setTarget(sf::Vector2i target, directionStates direction);
	void setBlinkyTarget(sf::Vector2i target);
	void setPinkyTarget(sf::Vector2i target, directionStates direction);
	void setInkyTarget(sf::Vector2i target, directionStates direction);
	void setClydeTarget(sf::Vector2i target);
	sf::Vector2i getTarget();
protected:
	std::string m_name;
	sf::Vector2i m_target;	
	//sf::RectangleShape m_targetRectangle;
	int m_frameOffsetY;
};
