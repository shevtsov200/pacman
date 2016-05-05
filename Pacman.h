#pragma once
#include <SFML\Graphics.hpp>
#include "Maze.h"
class Pacman : public sf::Drawable, public sf::Transformable
{
public: 
	Pacman(Maze *maze);
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

private:
	const static int FRAME_DURATION = 250;
	const static int NUMBER_OF_FRAMES = 3;
	const static int SPEED_DENOMINATOR = 2;

	int frameWidth;
	int frameHeight;
	int frameOffsetX;
	int spriteWidth;
	int spriteHeight;
	int spawnX;
	int spawnY;
	int tileSize;
	int scale;
	bool isDebugging;

	Maze *m_maze;

	sf::Sprite sprite;
	sf::Texture spriteSheet;

	sf::RectangleShape collisionBox;
	float speed;
	sf::Vector2f velocity;
	bool m_isMoving;

	float lastFrameTime;
	int frameX;
	int frameY;
	int frameIndex;

};
