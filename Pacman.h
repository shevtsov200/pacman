#pragma once
#include <SFML\Graphics.hpp>
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

private:
	const static bool IS_DEBUGGING = true;

	const static int SCALE = 3;

	const static int FRAME_DURATION = 250;
	const static int SHEET_TILE_SIZE = 8;
	const static int NUMBER_OF_FRAMES = 3;
	const static int FRAME_WIDTH = SHEET_TILE_SIZE * 2;
	const static int FRAME_HEIGHT = FRAME_WIDTH;
	const static int FRAME_OFFSETX = 56*SHEET_TILE_SIZE;

	const static int TILE_SIZE = SHEET_TILE_SIZE*SCALE;
	const static int SPRITE_WIDTH = TILE_SIZE;
	const static int SPRITE_HEIGHT = SPRITE_WIDTH;
	const static int SPAWNX = 14*TILE_SIZE;
	const static int SPAWNY = 23*TILE_SIZE;

	const static int SPEED_DENOMINATOR = 2;

	sf::Sprite sprite;
	sf::Texture spriteSheet;

	sf::Vector2f velocity;

	sf::RectangleShape collisionBox;
	float speed;
	bool m_isMoving;

	float lastFrameTime;
	int frameX;
	int frameY;
	int frameIndex;

};
