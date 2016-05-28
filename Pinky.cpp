#include "Pinky.h"

Pinky::Pinky()
{
	int speedDenominator = GameConstants::BLINKY_SPEED_DENOMINATOR;
	m_speed = (float)1 / speedDenominator;

	sf::Vector2i spawnPosition(21, 14);
	setInitialPosition(spawnPosition);
	m_frameOffsetY = GameConstants::FRAME_HEIGHT;
}
