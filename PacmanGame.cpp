#include "PacmanGame.h"

PacmanGame::PacmanGame()
{
	m_pacman;
}

void PacmanGame::processEvent(sf::Event event)
{
	if (event.type = sf::Event::KeyPressed)
	{
	m_pacman.changeDirection();
	}
}

void PacmanGame::update(sf::Clock clock)
{
	m_pacman.update(clock);
}

void PacmanGame::draw(sf::RenderTarget & target)
{
	target.clear(sf::Color::Black);
	target.draw(m_pacman);
}
