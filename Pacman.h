#pragma once
#include <SFML\Graphics.hpp>
class Pacman : public sf::Drawable, public sf::Transformable
{
public: 
	Pacman();
	//~Pacman();
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void changeDirection();
	void update(sf::Clock clock);
	void playAnimation(sf::Clock clock);

private:
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
	sf::Sprite sprite;
	sf::Texture spriteSheet;

	sf::Vector2f velocity;

	float lastFrameTime;
	int frameX;
	int frameY;
	int frameIndex;


};
