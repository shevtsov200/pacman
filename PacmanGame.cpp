#include "PacmanGame.h"

PacmanGame::PacmanGame()
{
	m_spriteSheet.loadFromFile("resources/spriteSheet3.png");
	m_pacmanSpriteSheet.loadFromFile("resources/spriteSheet2.png");

	m_maze.setTexture(m_spriteSheet);
	
	m_food = std::vector<Food>(GameConstants::MAZE_HEIGHT*GameConstants::MAZE_WIDTH, Food(m_spriteSheet));

	m_maze.buildWallMatrix(*m_walls, m_food, GameConstants::MAZE_HEIGHT, GameConstants::MAZE_WIDTH);

	m_debugCurrentTile.setSize(sf::Vector2f(GameConstants::TILE_SIZE, GameConstants::TILE_SIZE));
	m_debugCurrentTile.setPosition(GameConstants::SPAWNX, GameConstants::SPAWNY);
	m_debugCurrentTile.setFillColor(sf::Color::White);

	float x = 12;
	float y = 5;

	
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
	m_enemy.update(clock);
	
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
	target.draw(m_enemy);

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
	target.draw(m_debugCurrentTile);
}

int PacmanGame::pixelsToIndex(float x)
{
	return x / GameConstants::TILE_SIZE;
}

void PacmanGame::resolveCollision()
{
	int pacmanJ = pixelsToIndex(m_pacman.getCollisionBox().getGlobalBounds().left + m_pacman.getCollisionBox().getOrigin().x);
	int pacmanI = pixelsToIndex(m_pacman.getCollisionBox().getGlobalBounds().top + m_pacman.getCollisionBox().getOrigin().y);

	if (!m_pacman.getCollisionBox().getGlobalBounds().intersects(m_walls[pacmanI - 1][pacmanJ].getGlobalBounds()))
	{
		m_pacman.setFreePathState(m_pacman.UP);
	}
	if (!m_pacman.getCollisionBox().getGlobalBounds().intersects(m_walls[pacmanI + 1][pacmanJ].getGlobalBounds()))
	{
		m_pacman.setFreePathState(m_pacman.DOWN);
	}
	if (!m_pacman.getCollisionBox().getGlobalBounds().intersects(m_walls[pacmanI][pacmanJ - 1].getGlobalBounds()))
	{
		m_pacman.setFreePathState(m_pacman.LEFT);
	}
	if (!m_pacman.getCollisionBox().getGlobalBounds().intersects(m_walls[pacmanI][pacmanJ + 1].getGlobalBounds()))
	{
		m_pacman.setFreePathState(m_pacman.RIGHT);
	}
	m_pacman.m_testMovingUp = !m_pacman.getCollisionBox().getGlobalBounds().intersects(m_walls[pacmanI - 1][pacmanJ].getGlobalBounds());
	m_pacman.m_testMovingDown = !m_pacman.getCollisionBox().getGlobalBounds().intersects(m_walls[pacmanI + 1][pacmanJ].getGlobalBounds());
	m_pacman.m_testMovingLeft = !m_pacman.getCollisionBox().getGlobalBounds().intersects(m_walls[pacmanI][pacmanJ-1].getGlobalBounds());
	m_pacman.m_testMovingRight = !m_pacman.getCollisionBox().getGlobalBounds().intersects(m_walls[pacmanI][pacmanJ+1].getGlobalBounds());

	

	int enemyJ = pixelsToIndex(m_enemy.getCollisionBox().getGlobalBounds().left + m_enemy.getCollisionBox().getOrigin().x);
	int enemyI = pixelsToIndex(m_enemy.getCollisionBox().getGlobalBounds().top + m_enemy.getCollisionBox().getOrigin().y);

	if (!m_enemy.getCollisionBox().getGlobalBounds().intersects(m_walls[enemyI - 1][enemyJ].getGlobalBounds()))
	{
		m_enemy.setFreePathState(m_enemy.UP);
	}
	if (!m_enemy.getCollisionBox().getGlobalBounds().intersects(m_walls[enemyI + 1][enemyJ].getGlobalBounds()))
	{
		m_enemy.setFreePathState(m_enemy.DOWN);
	}
	if (!m_enemy.getCollisionBox().getGlobalBounds().intersects(m_walls[enemyI][enemyJ - 1].getGlobalBounds()))
	{
		m_enemy.setFreePathState(m_enemy.LEFT);
	}
	if (!m_enemy.getCollisionBox().getGlobalBounds().intersects(m_walls[enemyI][enemyJ + 1].getGlobalBounds()))
	{
		m_enemy.setFreePathState(m_enemy.RIGHT);
	}
	m_enemy.m_testMovingUp = !m_enemy.getCollisionBox().getGlobalBounds().intersects(m_walls[enemyI - 1][enemyJ].getGlobalBounds());
	m_enemy.m_testMovingDown = !m_enemy.getCollisionBox().getGlobalBounds().intersects(m_walls[enemyI + 1][enemyJ].getGlobalBounds());
	m_enemy.m_testMovingLeft = !m_enemy.getCollisionBox().getGlobalBounds().intersects(m_walls[enemyI][enemyJ - 1].getGlobalBounds());
	m_enemy.m_testMovingRight = !m_enemy.getCollisionBox().getGlobalBounds().intersects(m_walls[enemyI][enemyJ + 1].getGlobalBounds());
	
	//m_enemy.setTargetPosition(m_pacman.getCollisionBox().getGlobalBounds().left, m_pacman.getCollisionBox().getGlobalBounds().top);
	m_enemy.changeDirection(pacmanI, pacmanJ, enemyI, enemyJ);

	Food &currentFood = m_food[pacmanI*GameConstants::MAZE_WIDTH + pacmanJ];

	if (m_pacman.getCollisionBox().getGlobalBounds().intersects(currentFood.getCollisionRectangle()))
	{
		currentFood.setState(currentFood.DEVOURED);
	}
}
