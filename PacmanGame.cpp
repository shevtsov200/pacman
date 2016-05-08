#include "PacmanGame.h"

PacmanGame::PacmanGame()
{
	spriteSheet.loadFromFile("resources/spriteSheet3.png");
	pacmanSpriteSheet.loadFromFile("resources/spriteSheet2.png");

	m_maze;
	m_pacman;
	
	m_food = std::vector<Food>(GameConstants::MAZE_HEIGHT*GameConstants::MAZE_WIDTH, Food(spriteSheet));

	m_maze.buildWallMatrix(*m_walls, m_food, GameConstants::MAZE_HEIGHT, GameConstants::MAZE_WIDTH);

	debugCurrentTile.setSize(sf::Vector2f(GameConstants::TILE_SIZE, GameConstants::TILE_SIZE));
	debugCurrentTile.setPosition(GameConstants::SPAWNX, GameConstants::SPAWNY);
	debugCurrentTile.setFillColor(sf::Color::White);


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
	
	resolveCollision();
}

void PacmanGame::draw(sf::RenderTarget & target)
{
	target.clear(sf::Color::Black);
	target.draw(m_maze);

	for (int i = 0; i < GameConstants::MAZE_HEIGHT; i++)
	{
		for (int j = 0; j < GameConstants::MAZE_WIDTH; j++)
		{
			target.draw(m_food[i*GameConstants::MAZE_WIDTH+j]);
		}
	}

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
	target.draw(debugCurrentTile);
}

int PacmanGame::pixelsToIndex(float x)
{
	return x / GameConstants::TILE_SIZE;
}

void PacmanGame::resolveCollision()
{
	int j = pixelsToIndex(m_pacman.getCollisionBox().getGlobalBounds().left + m_pacman.getCollisionBox().getOrigin().x);
	int i = pixelsToIndex(m_pacman.getCollisionBox().getGlobalBounds().top + m_pacman.getCollisionBox().getOrigin().y);

	/*m_pacman.m_testMovingUp = !m_maze.isItWall(i - 1, j);
	m_pacman.m_testMovingDown = !m_maze.isItWall(i + 1, j);
	m_pacman.m_testMovingLeft = !m_maze.isItWall(i, j - 1);
	m_pacman.m_testMovingRight = !m_maze.isItWall(i, j + 1);*/

	m_pacman.m_testMovingUp = !m_pacman.getCollisionBox().getGlobalBounds().intersects(m_walls[i - 1][j].getGlobalBounds());
	m_pacman.m_testMovingDown = !m_pacman.getCollisionBox().getGlobalBounds().intersects(m_walls[i + 1][j].getGlobalBounds());
	m_pacman.m_testMovingLeft = !m_pacman.getCollisionBox().getGlobalBounds().intersects(m_walls[i][j-1].getGlobalBounds());
	m_pacman.m_testMovingRight = !m_pacman.getCollisionBox().getGlobalBounds().intersects(m_walls[i][j+1].getGlobalBounds());

	debugCurrentTile.setPosition(j*GameConstants::TILE_SIZE, i*GameConstants::TILE_SIZE);
}
