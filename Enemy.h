#pragma once
#include <SFML\Graphics.hpp>
class Enemy : public sf::Drawable, public sf::Transformable
{
public:
	enum directionStates { RIGHT, LEFT, UP, DOWN, NOWHERE };

	Enemy();
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void changeDirection(int targetI, int targetJ, int enemyI, int enemyJ);
	void changeHorizontalDirection(int targetJ, int enemyJ);
	void changeVerticalDirection(int targetI, int enemyJ);
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
	void stop();
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


	sf::Sprite m_sprite;
	sf::Texture m_spriteSheet;

	sf::Vector2f m_velocity;

	sf::RectangleShape m_collisionBox;
	sf::RectangleShape m_collisionBoxCenter;
	//sf::RectangleShape m_target;
	sf::Vector2i m_target;
	float m_speed;


	float m_lastFrameTime;
	int m_frameX;
	int m_frameY;
	int m_frameIndex;

};
