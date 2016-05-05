#include "PacmanGame.h"

PacmanGame::PacmanGame()
{
	m_maze;
	m_pacman;
	
	m_maze.buildWallMatrix(*m_walls, GameConstants::MAZE_HEIGHT, GameConstants::MAZE_WIDTH);
}

void PacmanGame::processEvent(sf::Event event)
{
	if (event.type = sf::Event::KeyPressed)
	{
		//if (resolveCollision())
		//{
		m_pacman.changeDirection();
		//}
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

	if (GameConstants::IS_DEBUGGING)
	{
		debugDraw(target);
	}
	
}

void PacmanGame::debugDraw(sf::RenderTarget & target) const
{
	for (int i = 0; i < GameConstants::MAZE_HEIGHT; i++)
	{
		for (int j = 0; j < GameConstants::MAZE_WIDTH; j++)
		{
			target.draw(m_walls[i][j]);
		}
	}
}

int PacmanGame::pixelsToIndex(float x)
{
	return x / GameConstants::TILE_SIZE;
}

void PacmanGame::resolveCollision()
{
	int j = pixelsToIndex(m_pacman.getCollisionBox().left);
	int i = pixelsToIndex(m_pacman.getCollisionBox().top);

	m_pacman.m_testMovingUp = !m_maze.isItWall(i-1, j);
	m_pacman.m_testMovingDown = !m_maze.isItWall(i+1, j);
	//m_pacman.m_testMovingLeft = !m_maze.isItWall(i, j-1);
	//m_pacman.m_testMovingRight = !m_maze.isItWall(i, j+1);
	
	/*for (int i = 0; i < GameConstants::MAZE_HEIGHT; i++)
	{
		for (int j = 0; j < GameConstants::MAZE_WIDTH; j++)
		{
			if (m_pacman.getCollisionBox().intersects(m_walls[i][j].getGlobalBounds()))
			//if(sf::Rect<float>(m_pacman.getCollisionBox().left, m_pacman.getCollisionBox().top+1, m_pacman.getCollisionBox().width, m_pacman.getCollisionBox().height).intersects(m_walls[i][j].getGlobalBounds()))
			{
				m_pacman.stop();
			}
		}
	}*/
	/*bool isMoving = true;
	int j = pixelsToIndex(m_pacman.getCollisionBox().left);
	int i = pixelsToIndex(m_pacman.getCollisionBox().top);

	//if ((m_pacman.getCollisionBox().intersects(m_walls[i+1][j].getGlobalBounds())) || (m_pacman.getCollisionBox().intersects(m_walls[i - 1][j].getGlobalBounds()) || (m_pacman.getCollisionBox().intersects(m_walls[i][j+1].getGlobalBounds()))|| (m_pacman.getCollisionBox().intersects(m_walls[i + 1][j-1].getGlobalBounds()))))
	if(m_pacman.getCollisionBox().intersects(m_walls[i][j].getGlobalBounds()))
	{
		m_pacman.stop();
	}*/
}
