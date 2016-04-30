#include "PacmanGame.h"

PacmanGame::PacmanGame()
{
	m_maze;
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
	m_maze.update();
	m_pacman.update(clock);
	
}

void PacmanGame::draw(sf::RenderTarget & target)
{
	target.clear(sf::Color::Black);
	target.draw(m_maze);
	target.draw(m_pacman);
	
}
