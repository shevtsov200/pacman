#pragma once
#include "Food.h"
typedef  std::vector < std::vector< int> > IntMatrix;
class Food; //{};
typedef	 std::vector < std::vector< Food> > FoodMatrix;

const static class GameConstants
{
public:
	const static bool IS_DEBUGGING = false;

	const static int SCALE = 3;
	const static int MAZE_WIDTH = 28;
	const static int MAZE_HEIGHT = 31;

	const static int SHEET_TILE_SIZE = 8;
	const static int FRAME_DURATION = 250;
	const static int TILE_SIZE = SHEET_TILE_SIZE*SCALE;

	const static int NUMBER_OF_FRAMES = 3;
	const static int FRAME_WIDTH = SHEET_TILE_SIZE * 2;
	const static int FRAME_HEIGHT = FRAME_WIDTH;
	const static int FRAME_OFFSETX = 56 * SHEET_TILE_SIZE;
	
	const static int NUMBER_OF_DEATH_FRAMES = 12;
	const static int DEATH_FRAME_OFFSETX = FRAME_OFFSETX + SHEET_TILE_SIZE * 2;

	const static int GHOST_SPRITE_WIDTH = FRAME_WIDTH;
	const static int GHOST_SPRITE_HEIGHT = FRAME_HEIGHT;
	const static int GHOST_SPRITEX = FRAME_OFFSETX;
	const static int GHOST_SPRITEY = FRAME_HEIGHT * 4;

	const static int GHOST_UPX = GHOST_SPRITEX + FRAME_WIDTH * 4;
	const static int GHOST_UPY = GHOST_SPRITEY;
	const static int GHOST_LEFTX = GHOST_SPRITEX + FRAME_WIDTH*2;
	const static int GHOST_LEFTY = GHOST_SPRITEY;
	const static int GHOST_DOWNX = GHOST_SPRITEX + FRAME_WIDTH * 6;
	const static int GHOST_DOWNY = GHOST_SPRITEY;
	const static int GHOST_RIGHTX = GHOST_SPRITEX;
	const static int GHOST_RIGHTY = GHOST_SPRITEY;

	const static int RIGHT_TUNNELX = MAZE_WIDTH*TILE_SIZE;
	//const static int RIGHT_TUNNELY = 14*TILE_SIZE;
	const static int LEFT_TUNNELX = 0;
	//const static int LEFT_TUNNELY = RIGHT_TUNNELY;

	const static int MAZE_SPRITE_WIDTH = MAZE_WIDTH*SHEET_TILE_SIZE;
	const static int MAZE_SPRITE_HEIGHT = MAZE_HEIGHT*SHEET_TILE_SIZE;
	const static int MAZE_SPRITEX = MAZE_SPRITE_WIDTH;
	const static int MAZE_SPRITEY = 0;

	const static int FOOD_SPRITEX = SHEET_TILE_SIZE;
	const static int FOOD_SPRITEY = FOOD_SPRITEX;

	const static int SPRITE_WIDTH = TILE_SIZE;
	const static int SPRITE_HEIGHT = SPRITE_WIDTH;
	const static int PACMAN_SPAWNI = 23;
	const static int PACMAN_SPAWNJ = 14;
	const static int PACMAN_SPAWNX = PACMAN_SPAWNJ * TILE_SIZE;
	const static int PACMAN_SPAWNY = PACMAN_SPAWNI * TILE_SIZE;

	const static int GHOST_SPAWNI = 5;
	const static int GHOST_SPAWNJ = 1;
	const static int GHOST_SPAWNX = GHOST_SPAWNJ * TILE_SIZE;
	const static int GHOST_SPAWNY = GHOST_SPAWNI * TILE_SIZE;

	const static int PACMAN_SPEED_DENOMINATOR = 6;
	const static int BLINKY_SPEED_DENOMINATOR = 8;

	const static int RESPAWN_TIME = 2;
	const static int FOOD_SCORE = 10;

};