#include "Clyde.h"

Clyde::Clyde()
{
	int speedDenominator = GameConstants::BLINKY_SPEED_DENOMINATOR;
	m_speed = (float)1 / speedDenominator;

	sf::Vector2i spawnPosition(GameConstants::GHOST_SPAWNJ, GameConstants::GHOST_SPAWNI);
	setInitialPosition(spawnPosition);
	m_frameOffsetY = GameConstants::FRAME_HEIGHT*3;
}
