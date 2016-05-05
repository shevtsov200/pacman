#include "PacmanGame.h"

PacmanGame::PacmanGame():m_maze(this),m_pacman(&m_maze)
{
	//m_maze = Maze(this);
}

void PacmanGame::processEvent(sf::Event event)
{
	if (event.type = sf::Event::KeyPressed)
	{
		if (resolveCollision())
		{
			//m_pacman->changeDirection();
		}
	}
}

void PacmanGame::update(sf::Clock clock)
{
	m_maze.update();
	//m_pacman->update(clock);
	
	resolveCollision();
}

void PacmanGame::draw(sf::RenderTarget & target)
{
	target.clear(sf::Color::Black);
	target.draw(m_maze);
	//target.draw(*m_pacman);
	
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

sf::Vector2<int> PacmanGame::pixelsToIndex(sf::Vector2f point)
{
	/*sf::Vector2<int> index;
	index.x = MAZE_WIDTH*
	return sf::Vector2<int>();*/
}

const int PacmanGame::getScale()
{
	return SCALE;
}

const int PacmanGame::getSheetTileSize()
{
	return SHEET_TILE_SIZE;
}

const int PacmanGame::getTileSize()
{
	return TILE_SIZE;
}

const bool PacmanGame::getIsDebugging()
{
	return IS_DEBUGGING;
}
