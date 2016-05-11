#pragma once
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
	
	const static int GHOST_SPRITE_WIDTH = FRAME_WIDTH;
	const static int GHOST_SPRITE_HEIGHT = FRAME_HEIGHT;
	const static int GHOST_SPRITEX = FRAME_OFFSETX;
	const static int GHOST_SPRITEY = FRAME_HEIGHT * 4;

	const static int MAZE_SPRITE_WIDTH = MAZE_WIDTH*SHEET_TILE_SIZE;
	const static int MAZE_SPRITE_HEIGHT = MAZE_HEIGHT*SHEET_TILE_SIZE;
	const static int MAZE_SPRITEX = MAZE_SPRITE_WIDTH;
	const static int MAZE_SPRITEY = 0;

	const static int FOOD_SPRITEX = SHEET_TILE_SIZE;
	const static int FOOD_SPRITEY = FOOD_SPRITEX;

	const static int SPRITE_WIDTH = TILE_SIZE;
	const static int SPRITE_HEIGHT = SPRITE_WIDTH;
	const static int SPAWNX = 14 * TILE_SIZE;
	const static int SPAWNY = 23 * TILE_SIZE;

	const static int GHOST_SPAWNX = 7 * TILE_SIZE;
	const static int GHOST_SPAWNY = 14 * TILE_SIZE;

	const static int SPEED_DENOMINATOR = 6;

};