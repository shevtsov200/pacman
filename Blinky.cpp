#include "Blinky.h"

Blinky::Blinky() : Enemy()
{
	int speedDenominator = GameConstants::BLINKY_SPEED_DENOMINATOR;
	m_speed = (float)1 / speedDenominator;

	sf::Vector2i spawnPosition(26, 5);
	setInitialPosition(spawnPosition);
	m_frameOffsetY = 0;
}
