#include "PacmanGame.h"

PacmanGame::PacmanGame()
{
	m_maze;
	m_pacman;
	
	m_maze.buildWallMatrix(*m_walls, MAZE_HEIGHT, MAZE_WIDTH);
}

void PacmanGame::processEvent(sf::Event event)
{
	if (event.type = sf::Event::KeyPressed)
	{
		if (resolveCollision())
		{
			m_pacman.changeDirection();
		}
	}
}

void PacmanGame::update(sf::Clock clock)
{
	m_maze.update();
	m_pacman.update(clock);
	
	resolveCollision();
}

void PacmanGame::draw(sf::RenderTarget & target)
{
	target.clear(sf::Color::Black);
	target.draw(m_maze);
	target.draw(m_pacman);

	if (IS_DEBUGGING)
	{
		debugDraw(target);
	}
	
}

void PacmanGame::debugDraw(sf::RenderTarget & target) const
{
	for (int i = 0; i < MAZE_HEIGHT; i++)
	{
		for (int j = 0; j < MAZE_WIDTH; j++)
		{
			target.draw(m_walls[i][j]);
		}
	}
}

bool PacmanGame::resolveCollision()
{
	bool isMoving = true;

//			if (m_pacman.getCollisionBox().intersects(m_walls[i][j].getGlobalBounds()))
	//		{
	//			m_pacman.setIsMoving(false);
	//		}

	return isMoving;
}
